#include "WindowController.h"

WindowController::WindowController()
{
	window = nullptr;
}

WindowController::~WindowController()
{
	if (window != nullptr)
	{
		glfwTerminate();
		window = nullptr;
	}
}

void WindowController::NewWindow()
{
	M_ASSERT(glfwInit(), "Failed to initialize GLFW. ");

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	M_ASSERT((window = glfwCreateWindow(1024, 768, "A sample scene", NULL, NULL)) != nullptr, "Failed to open GLFW window");
	glfwMakeContextCurrent(window);

}

Resolution WindowController::GetResolution()
{
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	return Resolution(mode->width, mode->height);
}