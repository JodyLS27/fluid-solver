#include "window/window.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


// GLFW Events
/**
* Called when resetting a windows size
**/
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	std::cout << "\n\n --- Window resized ---\n\n";
}

void engine::Window::init()
{
	// Initialize the window attributes
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// TODO: Place in the header at a later stage
	int m_width = 800;
	int m_height = 600;


	GLFWwindow* window = glfwCreateWindow(m_width, m_height, "Fluid Solver", NULL, NULL);

	// Crash if the window is null
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window\n";
		glfwTerminate();
		//return -1;

	}

	glfwMakeContextCurrent(window);


	// Pass GLAD the function to load the address of the OpenGL function pointer which is OS Specific.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Fail to Initialize GLAD\n";
		// return -1;
	}

	// Viewport
	glViewport(0, 0, m_width, m_height);

	// Event callbacks
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Render Loop
	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// End
	glfwTerminate();
	// return 0;
}
