#include "pch.h"
#include "EngineShared.h"

void EngineShared::MouseCallback(GLFWwindow* window, double x, double y)
{
	EngineShared::LAST_MOUSE_POS_X = static_cast<float>(x);
	EngineShared::LAST_MOUSE_POS_Y = static_cast<float>(y);
}

float EngineShared::GetMouseX()
{
	return EngineShared::LAST_MOUSE_POS_X;
}

float EngineShared::GetMouseY()
{
	return EngineShared::LAST_MOUSE_POS_Y;
}