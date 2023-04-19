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

class Camera
{
	GLint ShaderProjectionLoc = 0;
	GLint ShaderViewLoc = 0;

	mutable glm::vec3 ForwardDirection = glm::vec3(0.0f, 0.0f, -1.0f);
	const glm::vec3 UpDirection = glm::vec3(0.0f, 1.0f, 0.0f);

	bool useOrtho = false;
	float orthoZoomLevel = 14.0f;

	// Use these to De-Bounce the ortho/perspective change key input
	double LastPerspectiveModeSwitchTime = 0;
	double PerspectiveChangeDebounceTime = 0.25;

	glm::mat4 Projection = {};
	glm::mat4 View = {};
	Math::Vec3f Position = {};

public:
	void ResetProjectionMatrix();
	bool Init(GLuint shaderProgramId);

	void SetTranslate(float x, float y, float z);
	void SetXPosAbsolute(float x);
	void SetYPosAbsolute(float y);
	void SetZPosAbsolute(float z);
	void Move(float x, float y, float z);
	void Move(const glm::vec3 delta);
	void LookAt(float x, float y, float z);
	void SetFrameMatrix();
	void SetMoveSpeed(const float speed);
	void ProcessCameraInputs(const float deltaTime,
		GLFWwindow* window, Camera& cam);
	void SetCameraDirection(glm::vec3 normalizedDirection);
	void UpdateShader(GLuint shaderProgramId);


	float Fov = 45.0f;

	float LookSensitivity = 0.1f;
	float ZoomSensitivity = 0.05f;

	bool IsCameraMoveInitialized = false;
	float LastMouseXPos = 800.0f / 2.0;
	float LastMouseYPos = 600.0f / 2.0;

	float MoveSpeed = 0.25f;
	float MoveSpeedChangeSensitivity = 0.1f;
	float MoveSpeedMax = 10.0f;
	float MoveSpeedMin = 0.1f;

	Math::Euler Angle{ -15.0f,225.0f,0.0f };
};

