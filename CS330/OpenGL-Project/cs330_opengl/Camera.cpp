/*
 *
 *	Author: Dante Trisciuzzi
 *	Purpose: CS330 Project 2
 *	Date: 4.10.2023
 *
 */

#include "pch.h"
#include "Camera.h"

bool Camera::Init(const GLuint shaderProgramId)
{
	// use a try block in case the shader program throws an exception
	try {
		ResetProjectionMatrix();

		// Locate the variables in the shader program
		// .. we do not need to do this every frame
		this->ShaderProjectionLoc = glGetUniformLocation(shaderProgramId, "projection");
		this->ShaderViewLoc = glGetUniformLocation(shaderProgramId, "view");
	}catch(std::exception &e)
	{
		std::cerr << "Exception in Camera::Init(...): " << e.what() << std::endl;
		return false;
	}

	SetCameraDirection(Math::NormalizedDirectionFromEulerAngle(Angle));

	return true;
}

void Camera::ResetProjectionMatrix()
{

	if (!useOrtho) {
		this->Projection = glm::perspective(
			this->Fov,
			static_cast<GLfloat>(OpenGlConstants::OGL_WINDOW_SIZE.first)
			/ static_cast<GLfloat>(OpenGlConstants::OGL_WINDOW_SIZE.second),
			0.1f, 10000.0f);
		return;
	}


	// Calculate the ortographic scaling factor
	const float orthoFactor = 2.0f * this->orthoZoomLevel;

	// Apply ortho using Left hand coordinates
	this->Projection = 	glm::orthoRH(
		-(static_cast<GLfloat>(OpenGlConstants::OGL_WINDOW_SIZE.first) / orthoFactor),
		static_cast<GLfloat>(OpenGlConstants::OGL_WINDOW_SIZE.first) / orthoFactor,
		-(static_cast<GLfloat>(OpenGlConstants::OGL_WINDOW_SIZE.second) / orthoFactor),
		static_cast<GLfloat>(OpenGlConstants::OGL_WINDOW_SIZE.second) / orthoFactor,
		-1000.0f,
		1000.0f);

}


// Small wrapper for setting the view translation
void Camera::SetTranslate(const float x, const float y, const float z)
{
	this->Position.x = x;
	this->Position.y = y;
	this->Position.z = z;

	this->View = glm::translate(glm::vec3(Position.x, Position.y, Position.z));

}

void Camera::SetXPosAbsolute(const float x)
{
	this->Position.x = x;

	this->View = glm::translate(glm::vec3(Position.x, Position.y, Position.z));
}
void Camera::SetYPosAbsolute(const float y)
{
	this->Position.y = y;

	this->View = glm::translate(glm::vec3(Position.x, Position.y, Position.z));
}
void Camera::SetZPosAbsolute(const float z)
{
	this->Position.z = z;

	this->View = glm::translate(glm::vec3(Position.x, Position.y, Position.z));
}

void Camera::Move(const float x, const float y, const float z)
{
	this->Position.x += x;
	this->Position.y += y;
	this->Position.z += z;

	this->View = glm::translate(glm::vec3(Position.x, Position.y, Position.z));
}

void Camera::Move(const glm::vec3 delta)
{
	this->Position.x += delta.x;
	this->Position.y += delta.y;
	this->Position.z += delta.z;

	this->View = glm::translate(glm::vec3(Position.x, Position.y, Position.z));
}

void Camera::LookAt(const float x, const float y, const float z)
{
	this->View = glm::lookAt(
		glm::vec3(Position.x, Position.y, Position.z),
		glm::vec3(x,y,z),
		this->UpDirection);
}


// used to set the view and projection for each frame.
// ..called in the render loop
void Camera::SetFrameMatrix()
{
	this->View = glm::lookAt(
		glm::vec3(Position.x, Position.y, Position.z),
		glm::vec3(Position.x, Position.y, Position.z) + this->ForwardDirection,
		this->UpDirection
	);

	glUniformMatrix4fv(this->ShaderViewLoc, 
		1, GL_FALSE, glm::value_ptr(this->View));

	glUniformMatrix4fv(this->ShaderProjectionLoc, 
		1, GL_FALSE, glm::value_ptr(this->Projection));
}

void Camera::SetMoveSpeed(const float speed)
{
	this->MoveSpeed = speed;
}

void Camera::ProcessCameraInputs(const float deltaTime, GLFWwindow* window, Camera& cam)
{

	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
		// Debounce key input here
		// .. check time of last switch and compare to minimum acceptable time
		if(this->LastPerspectiveModeSwitchTime < glfwGetTime() - this->PerspectiveChangeDebounceTime)
		{
			this->useOrtho = !this->useOrtho;
			ResetProjectionMatrix();
			this->LastPerspectiveModeSwitchTime = glfwGetTime();
		}
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cam.Move(this->ForwardDirection * MoveSpeed);
		this->View = glm::lookAt(
			glm::vec3(Position.x, Position.y, Position.z),
			glm::vec3(Position.x, Position.y, Position.z) + this->ForwardDirection,
			this->UpDirection
		);
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cam.Move(-(this->ForwardDirection * MoveSpeed));
		this->View = glm::lookAt(
			glm::vec3(Position.x, Position.y, Position.z),
			glm::vec3(Position.x, Position.y, Position.z) + this->ForwardDirection,
			this->UpDirection
		);
	}

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		cam.Move(this->UpDirection * MoveSpeed);
		this->View = glm::lookAt(
			glm::vec3(Position.x, Position.y, Position.z),
			glm::vec3(Position.x, Position.y, Position.z) + this->ForwardDirection,
			this->UpDirection
		);
	}

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		cam.Move(-(this->UpDirection * MoveSpeed));
		this->View = glm::lookAt(
			glm::vec3(Position.x, Position.y, Position.z),
			glm::vec3(Position.x, Position.y, Position.z) + this->ForwardDirection,
			this->UpDirection
		);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		cam.Move(
			glm::normalize(
				glm::cross(
					ForwardDirection, UpDirection)) * this->MoveSpeed);
		this->View = glm::lookAt(
			glm::vec3(Position.x, Position.y, Position.z),
			glm::vec3(Position.x, Position.y, Position.z) + this->ForwardDirection,
			this->UpDirection
		);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		cam.Move(
			-(glm::normalize(
				glm::cross(
					ForwardDirection, UpDirection)) * this->MoveSpeed));
		this->View = glm::lookAt(
			glm::vec3(Position.x, Position.y, Position.z),
			glm::vec3(Position.x, Position.y, Position.z) + this->ForwardDirection,
			this->UpDirection
		);
	}
}

void Camera::SetCameraDirection(glm::vec3 normalizedDirection)
{
	this->ForwardDirection = normalizedDirection;
}

void Camera::UpdateShader(GLuint shaderProgramId)
{

	glUseProgram(shaderProgramId);

	GLint viewLoc = glGetUniformLocation(shaderProgramId, "view");
	GLint projLoc = glGetUniformLocation(shaderProgramId, "projection");

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(View));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(Projection));

	GLint viewPositionLoc = glGetUniformLocation(shaderProgramId, "viewPosition");

	glUniform3f(viewPositionLoc, Position.x, Position.y, Position.z);

}
