/*
 *
 *	Author: Dante Trisciuzzi
 *	Purpose: CS330 Project 2
 *	Date: 4.10.2023
 *
 */

#pragma once
#include "pch.h"

namespace OpenGlConstants
{
	const std::string OGL_WINDOW_TITLE = "CS330 Project 2 - Dante Trisciuzzi";
	constexpr std::pair<unsigned int, unsigned int> OGL_WINDOW_SIZE(1920, 1080);

	namespace Shaders
	{
		#ifndef GLSL
		#define GLSL(Version, Source) "#version " #Version " core \n" #Source
		#endif
		
		static const GLchar* ObjectVertexShaderSource = GLSL(440,
			layout(location = 0) in vec3 position;
			layout(location = 1) in vec3 normal;
			layout(location = 2) in vec2 textureCoordinate;

			out vec3 vertexNormal;
			out vec3 vertexFragmentPos;
			out vec2 vertexTextureCoordinate;

			uniform mat4 model;
			uniform mat4 view;
			uniform mat4 projection;

			void main()
			{
				gl_Position = projection * view * model * vec4(position, 1.0f);

				vertexFragmentPos = vec3(model * vec4(position, 1.0f));

				vertexNormal = mat3(transpose(inverse(model))) * normal;
				vertexTextureCoordinate = textureCoordinate;
			}
		);

		static const GLchar* ObjectFragmentShaderSource = GLSL(440,
		in vec3 vertexNormal;
		in vec3 vertexFragmentPos;
		in vec2 vertexTextureCoordinate;

		out vec4 fragmentColor;


		uniform vec3 mainLightColor;
		uniform vec3 mainLightLoc;
		uniform float mainAmbientMult;

		uniform vec3 fillLightColor;
		uniform vec3 fillLightLoc;
		uniform float fillAmbientMult;

		uniform vec3 objectColor;
		uniform vec3 viewPosition;
		uniform sampler2D uTexture;
		uniform vec2 uvScale;

		void main()
		{
			// Calculate the ambient lighting for the main and fill lights
			vec3 mainAmbient = mainAmbientMult * mainLightColor;
			vec3 fillAmbient = fillAmbientMult * fillLightColor;

			// Normalize the surface normal vector
			vec3 norm = normalize(vertexNormal);

			// Calculate the diffuse lighting for the main and fill lights
			vec3 mainLightDirection = normalize(mainLightLoc - vertexFragmentPos);
			vec3 mainLightDiffuse = max(dot(norm, mainLightDirection), 0.0) * mainLightColor;
			vec3 fillLightDirection = normalize(fillLightLoc - vertexFragmentPos);
			vec3 fillLighDiffuse = max(dot(norm, fillLightDirection), 0.0) * fillLightColor;

			// Calculate the specular lighting for the main and fill lights
			float specularIntensity = 1.5f;
			float highlightSize = 2.0f;
			vec3 viewDir = normalize(viewPosition - vertexFragmentPos);
			vec3 mainReflectionDirection = reflect(-mainLightDirection, norm);
			vec3 mainSpecularVec = specularIntensity
				* pow(max(dot(viewDir, mainReflectionDirection), 0.0), highlightSize)
				* mainLightColor;
			vec3 fillReflectionDirection = reflect(-fillLightDirection, norm);
			vec3 fillSpecularVec = specularIntensity
				* pow(max(dot(viewDir, fillReflectionDirection), 0.0), highlightSize)
				* fillLightColor;

			// Retrieve the texture color
			vec4 textureColor = texture(uTexture, vertexTextureCoordinate * uvScale);

			// Combine the ambient, diffuse, and specular components for the main and fill lights
			vec3 mainLightPhong = (mainAmbient + mainLightDiffuse + mainSpecularVec)
				* textureColor.xyz;

			vec3 fillLightPhong = (fillAmbient + fillLighDiffuse + fillSpecularVec)
				* textureColor.xyz;

			// Combine the main and fill light results and output the final fragment color
			fragmentColor = vec4(mainLightPhong + fillLightPhong, 1.0);
		}

		);
	}
}
