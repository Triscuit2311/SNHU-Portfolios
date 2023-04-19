/*
 *
 *	Author: Dante Trisciuzzi
 *	Purpose: CS330 Project 2
 *	Date: 4.10.2023
 *
 */

#pragma once
#include "pch.h"


class ShaderProgram
{
	GLuint ShaderProgramId;
	static bool CompileAndCheckShader(const GLuint shaderId);

	const GLchar* VertShaderSource;
	const GLchar* FragShaderSource;

public:
	ShaderProgram(const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource);
	~ShaderProgram();
	/**
	 * \brief Compiles the shaders and links the shader program
	 * \return false if compilation fails
	 */
	bool Compile() const;

	/**
	 * \brief Sets this shader program as the current gl shader program
	 */
	void SetCurrent() const;

	GLuint GetProgramId() const
	{
		return ShaderProgramId;
	}
};
