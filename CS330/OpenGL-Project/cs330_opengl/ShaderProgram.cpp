/*
 *
 *	Author: Dante Trisciuzzi
 *	Purpose: CS330 Project 2
 *	Date: 4.10.2023
 *
 */

#include "pch.h"
#include "ShaderProgram.h"

//  /*Shader program Macro*/
// #ifndef GLSL
// #define GLSL(Version, Source) "#version " #Version " core \n" #Source
// #endif
//
// const GLchar* VERTEX_SHADER_SOURCE = GLSL(440,
//     layout (location = 0) in vec3 position; // Vertex data from Vertex Attrib Pointer 0
//     layout (location = 1) in vec4 color;  // Color data from Vertex Attrib Pointer 1
//     layout (location = 2) in vec2 texCoords;  // Texture data from Vertex Attrib Pointer 2
//
//     out vec4 vertexColor; // variable to transfer color data to the fragment shader
// 	out vec2 textureCoords;
//
//     //Global variables for the  transform matrices
//     uniform mat4 model;
//     uniform mat4 view;
//     uniform mat4 projection;
//
//     void main()
//     {
//         gl_Position = projection * view * model * vec4(position, 1.0f); // transforms vertices to clip coordinates
//         vertexColor = color; // references incoming color data
// 		textureCoords = texCoords;
//     }
// );
//
// const GLchar* FRAGMENT_SHADER_SOURCE = GLSL(440,
// 	in vec4 vertexColor; // Variable to hold incoming color data from vertex shader
// in vec2 textureCoords;
//
// out vec4 fragmentColor;
//
// uniform sampler2D uTexture;
//
// void main()
// {
//
// 	fragmentColor = texture(uTexture, textureCoords) * vertexColor;
// }
// );




bool ShaderProgram::CompileAndCheckShader(const GLuint shaderId)
{
	int compileSuccess = 0;
	// Compile shader
	glCompileShader(shaderId);

	// Pull shader compile status code
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileSuccess);

	// On failed compilation, show error log
	if (!compileSuccess)
	{
		char compileErrorLog[512];
		glGetShaderInfoLog(shaderId, 512, nullptr, compileErrorLog);
		std::cout << "Shader Compile failed!\nLog: " << compileErrorLog << std::endl;
		return false;
	}

	return true;
}

ShaderProgram::ShaderProgram(const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource)
{
	this->VertShaderSource = vertexShaderSource;
	this->FragShaderSource = fragmentShaderSource;

	// Create a program object
	this->ShaderProgramId = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
	// Delete the shader program from VRAM
	glDeleteProgram(this->ShaderProgramId);
}

bool ShaderProgram::Compile() const
{
	// Create the shader objects
	const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Set the shaders' source
	glShaderSource(vertexShader, 1, &this->VertShaderSource, nullptr);
	glShaderSource(fragmentShader, 1, &this->FragShaderSource, nullptr);

	// Compile shaders and check for errors
	if (!CompileAndCheckShader(vertexShader) ||
		!CompileAndCheckShader(fragmentShader))
	{
		return false;
	}

	// Attach shaders to program
	glAttachShader(this->ShaderProgramId, vertexShader);
	glAttachShader(this->ShaderProgramId, fragmentShader);

	int linkerSuccess = 0;
	// Link Program and ensure success
	glLinkProgram(this->ShaderProgramId);

	// Pull linker success code
	glGetProgramiv(this->ShaderProgramId, GL_LINK_STATUS, &linkerSuccess);

	// On failure, display linker log
	if (!linkerSuccess)
	{
		// Show linker errors
		char linkerErrorLog[512];
		glGetProgramInfoLog(this->ShaderProgramId, sizeof(linkerErrorLog), nullptr, linkerErrorLog);
		std::cout << "Shader Program link failed!\nLog: " << linkerErrorLog << std::endl;
	}

	

	return true;
}

void ShaderProgram::SetCurrent() const
{
	// Set current OpenGL shader to this program
	glUseProgram(this->ShaderProgramId);
}
