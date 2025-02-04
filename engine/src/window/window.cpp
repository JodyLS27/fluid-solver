#include "window/window.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

engine::Window::Window() : m_window(nullptr) {}

engine::Window::~Window()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}


void engine::Window::init()
{
	// Initialize the window attributes
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

// GLFW Events
/**
* Called when resetting a windows size
**/
void engine::Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	std::cout << "\n\n --- Window resized ---\n\n";
}

void engine::Window::process_input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}
