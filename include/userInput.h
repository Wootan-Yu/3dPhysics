#pragma once
#include <GLFW/glfw3.h>
#include "global.h"

struct UserInput
{
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};