/*
 *
 *	Author: Dante Trisciuzzi
 *	Purpose: CS330 Project 2
 *	Date: 4.10.2023
 *
 */

#include "pch.h"
#include "Mesh.h"

#include "Camera.h"
#include "RandomHelpers.h"


Mesh::Mesh() = default;

Mesh::Mesh(const std::vector<Math::Vertex>& vertices,
           const std::vector<Math::Tri>& triangles, GLuint textureId)
{
	this->TextureId = textureId;
	this->vertexArray = Math::FloatVectorFromVerts(vertices);
	this->elementIndices = Math::ShortVectorFromTris(triangles);
}

Mesh::~Mesh()
{
	// Delete the VAO from the GPU VRAM
	glDeleteVertexArrays(1, &this->VertexArrayObject);

	// Delete the VBOs from the GPU VRAM
	glDeleteBuffers(2, this->VertexBufferObjectArr);
}

bool Mesh::SetMeshVerts(const std::vector<Math::Vertex>& vertices)
{
	this->vertexArray = Math::FloatVectorFromVerts(vertices);
	return true;
}

bool Mesh::SetMeshTris(const std::vector<Math::Tri>& triangles)
{
	this->elementIndices = Math::ShortVectorFromTris(triangles);
	return true;
}

bool Mesh::CreateMesh()
{
	try
	{
		// Generate vertex array and bind to it
		glGenVertexArrays(1, &this->VertexArrayObject);
		glBindVertexArray(this->VertexArrayObject);

		// Generate vertex buffers, bind to it
		glGenBuffers(2, this->VertexBufferObjectArr);
		glBindBuffer(GL_ARRAY_BUFFER, this->VertexBufferObjectArr[0]);


		
		// Populate buffer with vertex data
		glBufferData(GL_ARRAY_BUFFER, this->vertexArray.size() * sizeof(float),
			this->vertexArray.data(), GL_STATIC_DRAW);
		
				// Creates a buffer object for the IndexCount
		this->IndexCount = this->elementIndices.size() * sizeof(unsigned short);
		
		// Bind the other vertex buffer & populate with index data
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,
		             this->VertexBufferObjectArr[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			this->elementIndices.size() * sizeof(unsigned short), this->elementIndices.data(), GL_STATIC_DRAW);


		// Creates the Vertex Attribute Pointers
		glVertexAttribPointer(0, this->NumValuesEachVertexPosition,
		                      GL_FLOAT, GL_FALSE, this->Stride, nullptr);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, this->NumValuesEachVertexNormal,
		                      GL_FLOAT, GL_FALSE, this->Stride,

		                      reinterpret_cast<char*>(sizeof(float) * this->NumValuesEachVertexPosition));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, this->NumValuesEachVertexTextureCoord,
			GL_FLOAT, GL_FALSE, this->Stride,
			reinterpret_cast<char*>(sizeof(float) * (this->NumValuesEachVertexPosition + this->NumValuesEachVertexNormal)));
		glEnableVertexAttribArray(2);
	}
	catch (std::exception& e)
	{
		std::cerr << "Mesh Creation failed! Error: " << e.what() << std::endl;
		return false;
	}
	

	return true;
}

void Mesh::Render(const GLuint shaderProgramId)
{
	//TODO: Why does the first bound texture cover everything
	//.. When we're changing it per object to reflect the ID

	glUseProgram(shaderProgramId);
	const GLuint texLocation = glGetUniformLocation(shaderProgramId, "uTexture");

	glUniform1i(texLocation, this->TextureId);
	
	// bind textures on corresponding texture units
	glActiveTexture(GL_TEXTURE0 + this->TextureId);
	glBindTexture(GL_TEXTURE_2D, this->TextureId);

	

	const GLuint transformLocation = 
		glGetUniformLocation(shaderProgramId, "model");

	GLint objectColorLoc = glGetUniformLocation(shaderProgramId, "objectColor");
	glUniform3f(objectColorLoc, 0.5f,0.5f,0.5f);

	GLint UVScaleLoc = glGetUniformLocation(shaderProgramId, "uvScale");
	glUniform2fv(UVScaleLoc, 1, glm::value_ptr(glm::vec2{1,1}));

	glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transform));

	// Bind to the VAO
	glBindVertexArray(this->VertexArrayObject);

	// Draw based on the indices
	glDrawElements(GL_TRIANGLES, this->IndexCount,
	               GL_UNSIGNED_SHORT, nullptr);

	// Unbind from the VAO
	glBindVertexArray(0);

}


void Mesh::SetRotation(const float x, const float y, const float z)
{
	this->Rotation = { x,y,z };

	this->transform =
		(glm::translate(glm::vec3(Translation.X, Translation.Y, Translation.Z))
			* glm::rotate(
				glm::radians(90.0f), glm::vec3(Rotation.X, Rotation.Y, Rotation.Z))
			* glm::scale(glm::vec3(Scale.X, Scale.Y, Scale.Z)));
}

void Mesh::SetScale(const float x, const float y, const float z)
{
	this->Scale = { x,y,z };

	this->transform =
		(glm::translate(glm::vec3(Translation.X, Translation.Y, Translation.Z))
			* glm::rotate(
				glm::radians(90.0f), glm::vec3(Rotation.X, Rotation.Y, Rotation.Z))
			* glm::scale(glm::vec3(Scale.X, Scale.Y, Scale.Z)));
}

void Mesh::SetTranslation(const float x, const float y, const float z)
{
	this->Translation = { x,y,z };

	this->transform =
		(glm::translate(glm::vec3(Translation.X, Translation.Y, Translation.Z))
			* glm::rotate(
				glm::radians(90.0f), glm::vec3(Rotation.X, Rotation.Y, Rotation.Z))
			* glm::scale(glm::vec3(Scale.X, Scale.Y, Scale.Z)));
}


void Mesh::Rotate(float x, float y, float z, float amt)
{
	this->transform = glm::rotate(this->transform, glm::radians(amt), glm::vec3(x,y,z));
}

void Mesh::Move(float x, float y, float z)
{
	this->transform = glm::translate(this->transform, glm::vec3(x, y, z));
}

Cylinder::Cylinder(const int segments, 
	const float radius,
	const float length,
	GLuint textureID,
	const bool mapTextureRepeating,
	bool staticNormalY) : Mesh()
{
	// We want the center of the object to be th origin point
	const float objectCenterOffset = length / 2;

	// Containers for verts/tris
	std::vector<Math::Vertex> vertices{};
	std::vector<Math::Tri> triangles{};


	// first circle center point
	vertices.push_back(
		{
			0, 0, -objectCenterOffset,
			0.0f,
			0.0f,
			0.0f, 1.0f, 0.0f
		}
	);


	float normalY = 0.0f;
	float increment = 1.0f / (segments * 2);
	bool inc = true;
	int texUIndex = 0;
	// first circle
	// .. Adds vertex for each point, based on segments
	// .. Then adds triangles to the center point
	for (const auto& pt :
		Math::GetCirclePoints(0, 0, radius, segments))
	{
		float textureU = 0.0f;
		if (mapTextureRepeating) {
			textureU = texUIndex % 2 == 0 ? 0.0f : 1.0f;
		}
		else
		{
			textureU = (1.0f / segments) * texUIndex;
		}
		texUIndex++;


		if (normalY >= .50f) inc = false;
		if (normalY <= 0.0f) inc = true;
		normalY += inc ? increment : -increment;

		// Add the vertex
		vertices.push_back(
			{
				pt.first,
				pt.second,
				-objectCenterOffset,
				0.1f,
				staticNormalY ? 0.3f : normalY,
				0.1f,
				textureU,
				0.0f
			}
		);

		// track this index
		const int thisIndex = vertices.size() - 1;

		// break on last index
		if (thisIndex == segments + 1)
			break;

		// Set next index
		int nextIndex = thisIndex + 1;

		// for the last slice triangle we use the first point of the circumference
		if (thisIndex == segments)
		{
			nextIndex = 1;
		}

		// Add Tri
		triangles.push_back(
			{
				0, //center
				thisIndex,
				nextIndex
			}
		);
	}

	const int secondCircleCenterIndex = vertices.size();

	// second center
	vertices.push_back(
		{
			0, 0, objectCenterOffset,
			0.0f,
			0.0f,
			0.0f, 1.0f, 1.0f
		}
	);


	normalY = 0.0f;
	inc = true;
	texUIndex = 0;
	// second circle, same as the first
	for (const auto& pt : Math::GetCirclePoints(0, 0, radius, segments))
	{
		float textureU = 0.0f;
		if (mapTextureRepeating) {
			textureU = texUIndex % 2 == 0 ? 1.0f : 0.0f;
		}
		{
			textureU = (1.0f / segments) * texUIndex;
		}
		texUIndex++;

		if (normalY >= .50f) inc = false;
		if (normalY <= 0.0f) inc = true;
		normalY += inc ? increment : -increment;


		// Add the vertex
		vertices.push_back(
			{
				pt.first,
				pt.second,
				objectCenterOffset,
				0.1f,
				staticNormalY ? 1.0f : normalY,
				0.1f,
				textureU,
				1.0f
			}
		);

		const int thisIndex = vertices.size() - 1;
		if (thisIndex == secondCircleCenterIndex + segments + 1)
			break;
		int nextIndex = thisIndex + 1;

		// for the last slice triangle we use the first point of the circumference
		// .. of the second circle
		if (thisIndex == secondCircleCenterIndex + segments)
		{
			nextIndex = secondCircleCenterIndex + 1;
		}

		triangles.push_back(
			{
				secondCircleCenterIndex, //center of second circle
				thisIndex,
				nextIndex
			}
		);
	}


	// side segments
	for (int i = 1; i <= segments; ++i)
	{

		// For the last segment, we reuse the first index of each circle
		if (i == segments)
		{
			triangles.push_back(
				{
					i,
					segments * 2 + 1,
					segments + 2,
				});

			triangles.push_back(
				{
					i,
					 1,
					segments + 2
				});

			break;
		}

		// Create triangle with the respective vertex on the second circle
		// .. and it's next vertex
		triangles.push_back(
			{
				i,
				i + segments + 1,
				i + segments + 2
			});

		// Create triangle with the next vertex, and it's respective vertex
		// .. on the second circle
		triangles.push_back(
			{
				i,
				i + 1,
				i + segments + 2
			});

	}

	//Setup verts/tris
	this->SetMeshVerts(vertices);
	this->SetMeshTris(triangles);
	this->TextureId = textureID;

	// Instantiate the vert and tri arrays in the mesh object
	this->CreateMesh();
}

Cone::Cone(const int segments,
	const float radius,
	const float height,
	const GLuint textureID,
	const bool mapTextureRepeating,
	float minColorValue, float maxColorValue)
{
	// We want the center of the object to be th origin point
	const float objectCenterOffset = height / 2;

	// Containers for verts/tris
	std::vector<Math::Vertex> vertices{};
	std::vector<Math::Tri> triangles{};


	// circle center point
	vertices.push_back(
		{
			0, 0, -objectCenterOffset,
			0.5f,
			-1.0f,
			0.5f,
			0.5f,1.0f
		}
	);


	float normalY = 0.50f;
	float increment = 1.0f / (segments * 2);
	bool inc = false;

	// circle
	// .. Adds vertex for each point, based on segments
	// .. Then adds triangles to the center point
	for (const auto& pt :
		Math::GetCirclePoints(0, 0, radius, segments))
	{
		float textureU = 0.0f;
		if (mapTextureRepeating) {
			textureU = vertices.size() % 2 == 0 ? 0.0f : 1.0f;
		}else
		{
			textureU = (1.0f / segments)* vertices.size();
		}

		normalY += inc ? increment : -increment;
		if (normalY >= .50f) inc = false;
		if (normalY <= 0.0f) inc = true;

		// Add the vertex
		vertices.push_back(
			{
				pt.first,
				pt.second,
				-objectCenterOffset,
			0.0f,
			normalY,
				0.0f,
				// U
			textureU,
				0 // V
			}
		);


		// track this index
		const int thisIndex = vertices.size() - 1;

		// break on last index
		if (thisIndex == segments + 1)
			break;

		// Set next index
		int nextIndex = thisIndex + 1;

		// for the last slice triangle we use the first point of the circumference
		if (thisIndex == segments)
		{
			nextIndex = 1;
		}

		// Add Tri
		triangles.push_back(
			{
				0, //center
				thisIndex,
				nextIndex
			}
		);
	}


	vertices.push_back(
		{
			0, 0, objectCenterOffset,
			0.0f,
			0.0f,
			0.0f,
			0.5f,1.0f
		}
	);


	int last = vertices.size() - 1;
	// segments
	for (int i = 1; i <= segments; ++i)
	{
		// For the last segment, we reuse the first index of each circle
		if (i == segments)
		{
			triangles.push_back(
				{
					i,
				1,
				last
				});

			break;
		}
		
		triangles.push_back(
			{
				i,
				i + 1,
				last
			});
	}


	//Setup verts/tris
	this->SetMeshVerts(vertices);
	this->SetMeshTris(triangles);
	this->TextureId = textureID;

	// Instantiate the vert and tri arrays in the mesh object
	this->CreateMesh();
}



Plane::Plane(const float width, const float height, const GLuint textureId,
	float minColorValue, float maxColorValue)
{
	// We want the center of the object to be th origin point
	const float objectWidthCenterOffset = width / 2;
	const float objectHeightCenterOffset = height / 2;

	// Containers for verts/tris
	std::vector<Math::Vertex> vertices{};
	std::vector<Math::Tri> triangles{};


	// bottom left
	vertices.push_back(
		{
			-objectWidthCenterOffset, 0, -objectHeightCenterOffset,
			0.0f,
			1.0f,
			0.0f,
			0.0f,0.0f
		}
	);

	// bottom right
	vertices.push_back(
		{
			objectWidthCenterOffset, 0, -objectHeightCenterOffset,
			0.0f,
			1.0f,
			0.0f,
			1.0f,0.0f
		}
	);

	// top left
	vertices.push_back(
		{
			-objectWidthCenterOffset, 0, objectHeightCenterOffset,
			0.0f,
			1.0f,
			0.0f,
			0.0f,1.0f
		}
	);

	// top right
	vertices.push_back(
		{
			objectWidthCenterOffset, 0, objectHeightCenterOffset,
			0.0f,
			1.0f,
			0.0f,
			1.0f,1.0f
		}
	);

	triangles.push_back(
		{
			0,1,2
		});
	triangles.push_back(
		{
			1,2,3
		});

	//Setup verts/tris
	this->SetMeshVerts(vertices);
	this->SetMeshTris(triangles);
	this->TextureId = textureId;

	// Instantiate the vert and tri arrays in the mesh object
	this->CreateMesh();

}
