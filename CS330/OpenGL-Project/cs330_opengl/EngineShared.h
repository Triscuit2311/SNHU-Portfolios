#pragma once
#include "pch.h"

namespace  EngineShared
{
	static float LAST_MOUSE_POS_X;
	static float LAST_MOUSE_POS_Y;

	void MouseCallback(GLFWwindow* window, double x, double y);
	float GetMouseX();
	float GetMouseY();
}