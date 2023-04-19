/*
 *
 *	Author: Dante Trisciuzzi
 *	Purpose: CS330 Project 2
 *	Date: 4.10.2023
 *
 */

#pragma once


class OpenGlWindowManager
{
	GLFWwindow* oglWindow;

	void SetupGLFWProfile();
	bool CreateGlWindowObject();


	void SetupWindowCallbacks() const;
	bool SetupGLEW();
	void ProcessUserInputs() const;

	struct TimeVars
	{
		mutable float Delta = 0;
		mutable float Frame = 0;
		mutable float LastFrame = 0;
	};

	TimeVars Time;
	void UpdateTime() const;

public:
	OpenGlWindowManager();
	~OpenGlWindowManager();

	/**
	 * \brief Sets the OpenGL clear color of the GLFW window
	 * \param r Red
	 * \param g Gren
	 * \param b Blue
	 */
	static void SetWindowBackgroundColor(float r, float g, float b);


	/**
	 * \brief Initializes a new GLFW Window, and GLEW.
	 * \return true if Initialization was successful, false otherwise.
	 */
	bool Init();


	/**
	 * \brief Renders the GLFW window, performs all strictly required functions, handles user inputs.
	 * \param renderCallback Callback for rendering tasks
	 * \param inputCallback Callback for input handling
	 * \return True unless exception is raised.
	 */
	bool RenderLoop(
		const std::function<void()>& renderCallback,
		const std::function<void(GLFWwindow*)> inputCallback) const;


	void ProcessInputs(const std::function<void(GLFWwindow*)>& inputCallback) const;

	float GetDelta() const;

	GLFWwindow* GetWindowPtr();

};
