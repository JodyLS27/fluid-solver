#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <array>

#include "engine.hpp"


// Temp Data for testing
const char* vertex_shader_source = "#version 330 core\n"
"layout(location = 0) in vec3 aPos; \n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
"}\0";

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

	// Build and Comile our Shader Program
	// ------------------------------------------------
	// Vertex Shader
	unsigned int vertex_shader{};

	// Checking if shader comiliation was successful
	int shader_vertex_success{};
	char info_log[512];


	vertex_shader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertex_shader, 1, &vertex_shader_source, nullptr);
	glCompileShader(vertex_shader);

	// Check Compiliation success
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &shader_vertex_success);

	if (!shader_vertex_success)
	{
		glGetShaderInfoLog(vertex_shader, 512, nullptr, info_log);
		std::cout << "ERROR::SHADER::VERTEX::COMPILE FAILED\n" << info_log << "\n";
	}

	// Vertex Data
	float vertices[] =
	{
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	// Setup Vertex Buffer Object
	unsigned int VBO{};
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	// ------------------------------------------------

	// Main loop
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