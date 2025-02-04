#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "engine.hpp"


void engine::Engine::init()
{
}

int engine::Engine::start()
{
	m_engine_window.init();

	m_window = m_engine_window.getGLFWwindow();

	if (!m_window)
	{
		return -1;
	}

	while (!glfwWindowShouldClose(m_window))
	{
		// Input
		m_engine_window.process_input(m_window);

		// Rendering
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	return 0;
}