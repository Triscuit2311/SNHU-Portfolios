/*
 *
 *	Author: Dante Trisciuzzi
 *	Purpose: CS330 Project 2
 *	Date: 4.10.2023
 *
 */

#include "pch.h"
#include "OpenGlWindowManager.h"


void OpenGlWindowManager::SetWindowBackgroundColor(const float r, const float g, const float b)
{
	// Setup background (buffer clear color)
	glClearColor(r, g, b, 1.0f);
}

bool OpenGlWindowManager::Init()
{
	SetupGLFWProfile();

	if (!CreateGlWindowObject()) return false;

	SetupWindowCallbacks();

	SetWindowBackgroundColor(0.0f, 0.0f, 0.0f);

	if (!SetupGLEW()) return false;

	glfwSetInputMode(oglWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	return true;
}

bool OpenGlWindowManager::RenderLoop(
	const std::function<void()>& renderCallback,
	const std::function<void(GLFWwindow*)> inputCallback) const
{
	// Use try block to catch exceptions in render loop
	// .. so that we can properly shut down the GLFW context
	try
	{
		// Check if the flag is set to close the window
		// .. run render loop while the flag is NOT set
		while (!glfwWindowShouldClose(oglWindow))
		{
			// Perform time calculations
			UpdateTime();

			// Check for user inputs
			ProcessInputs(inputCallback);

			// Use Z buffer depth check
			glEnable(GL_DEPTH_TEST);

			// Clear background
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Perform all rendering in callback
			renderCallback();

			// Swap buffers and check for new events
			glfwSwapBuffers(oglWindow);
			glfwPollEvents();
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		glfwTerminate();
		return false;
	}

	return true;
}

void OpenGlWindowManager::ProcessInputs(const std::function<void(GLFWwindow*)>& inputCallback) const
{
	// Setup escape key to close the window
	if (glfwGetKey(oglWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(oglWindow, true);

	inputCallback(this->oglWindow);
}

float OpenGlWindowManager::GetDelta() const
{
	return Time.Delta;
}

GLFWwindow* OpenGlWindowManager::GetWindowPtr()
{
	return oglWindow;
}

void OpenGlWindowManager::SetupGLFWProfile()
{
	// Init and set glfw version/profile
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

bool OpenGlWindowManager::CreateGlWindowObject()
{
	// init ogl window object
	oglWindow = glfwCreateWindow(
		OpenGlConstants::OGL_WINDOW_SIZE.first, OpenGlConstants::OGL_WINDOW_SIZE.second,
		OpenGlConstants::OGL_WINDOW_TITLE.c_str(), nullptr, nullptr);

	// ensure ogl window object was created successfully
	if (oglWindow == nullptr)
	{
		std::cerr << "glfwCreateWindow failed to create window or pointer mismatch." << std::endl;
		return false;
	}
	return true;
}

void OpenGlWindowManager::SetupWindowCallbacks() const
{
	// Setup OpenGL Context & set frame resize callback
	// .. good candidate for a lambda rather than a small global function
	glfwMakeContextCurrent(oglWindow);

	glfwSetFramebufferSizeCallback(oglWindow,
	                               [](auto window, const int width, const int height)
	                               {
		                               glViewport(0, 0, width, height);
		                               return (void)nullptr;
	                               });
}

bool OpenGlWindowManager::SetupGLEW()
{
	// Init GLEW & ensure init success
	glewExperimental = GL_TRUE;
	GLenum GlewInitResult = glewInit();
	if (GlewInitResult != GLEW_OK)
	{
		std::cerr << "glewInit() failed: " << glewGetErrorString(GlewInitResult) << std::endl;
		return false;
	}
	return true;
}


void OpenGlWindowManager::UpdateTime() const
{
	Time.Frame = glfwGetTime();
	Time.Delta = Time.Frame - Time.LastFrame;
	Time.LastFrame = Time.Frame;
}

OpenGlWindowManager::OpenGlWindowManager()
{
	oglWindow = nullptr;
}

OpenGlWindowManager::~OpenGlWindowManager()
{
	glfwTerminate();
}
