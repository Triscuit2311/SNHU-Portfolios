/*
 *
 *	Author: Dante Trisciuzzi
 *	Purpose: CS330 Project 2
 *	Date: 4.10.2023
 *
 */

#pragma once
#include "pch.h"
#include "Math.h"

class Mesh
{
protected:
	GLuint TextureId = 1;

private:
	GLuint VertexArrayObject = 0;
	GLuint VertexBufferObjectArr[2] = {};
	GLsizei IndexCount = 0;

	// calculate vertex stride
	const GLuint NumValuesEachVertexPosition = 3;
	const GLuint NumValuesEachVertexNormal = 3;
	const GLuint NumValuesEachVertexTextureCoord = 2;
	const GLint Stride = sizeof(float) * 
		(NumValuesEachVertexPosition + NumValuesEachVertexNormal + NumValuesEachVertexTextureCoord);

	// Using a custom struct to modify the 
	struct Vec3
	{
		float X;
		float Y;
		float Z;
	};

	Vec3 Translation = {0,0,0};
	Vec3 Rotation = {1,0,0};
	
	Vec3 Scale = {1,1,1};

	std::vector<float> vertexArray;
	//
	std::vector<unsigned short> elementIndices;

	std::vector<Math::Vertex> Vertices;
	std::vector<Math::Tri> Triangles;

	Vec3 NextRotate = { 0,0,0 };
	bool NeedsRotate = false;

	glm::mat4 transform = {};
	
public:
	Mesh();
	Mesh(const std::vector<float>& vertices, const std::vector<unsigned short>& indices);
	Mesh(const std::vector<Math::Vertex>& vertices,
		const std::vector<Math::Tri>& triangles, GLuint textureId);

	~Mesh();


	bool SetMeshVerts(const std::vector<Math::Vertex>& vertices);
	bool SetMeshTris(const std::vector<Math::Tri>& triangles);

	/**
	 * \brief Creates a mesh object
	 * \return false if exception is thrown
	 */
	bool CreateMesh();


	/**
	 * \brief Renders the mesh object via indices with DrawElements(...)
	 */
	void Render(const GLuint shaderProgramId);

	void Rotate(float x, float y, float z, float amt);
	void Move(float x, float y, float z);

	// Setters to modify the mesh at runtime
	void SetRotation(float x, float y, float z);
	void SetScale(float x, float y, float z);
	void SetTranslation(float x, float y, float z);
};

class Cylinder : public Mesh
{
public:
	Cylinder(int segments, float radius, float length,
		GLuint textureID, bool mapTextureRepeating,
		bool staticNormalY = false);
};

class Cone : public Mesh
{
public:
	Cone(int segments, float radius, 
		float height, GLuint textureId, bool mapTextureRepeating = false,
		float minColorValue = 0.0f, float maxColorValue = 1.0f);
};

class Plane : public Mesh
{
public:
	Plane(float width, float height,
		GLuint textureId,
		float minColorValue = 0.0f, float maxColorValue = 1.0f);
};