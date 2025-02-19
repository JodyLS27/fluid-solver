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

const char* fragment_shader_source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
"}\n";

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

	// Checking if shader comiliation was successful
	int success{};
	char info_log[512];


	// --- Vertex Shader ---
	unsigned int vertex_shader{};
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertex_shader, 1, &vertex_shader_source, nullptr);
	glCompileShader(vertex_shader);

	//Vertex Compiliation success
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertex_shader, 512, nullptr, info_log);
		std::cout << "ERROR::SHADER::VERTEX::COMPILE FAILED\n" << info_log << "\n\n";
	}

	// --- Fragment Shader ---
	unsigned int fragment_shader{};
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragment_shader, 1, &fragment_shader_source, nullptr);
	glCompileShader(fragment_shader);

	// Fragment Compilation success
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragment_shader, 512, nullptr, info_log);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILED FAILED\n" << info_log << "\n\n";
	}

	// --- Shader Program ---
	unsigned int shader_program{};
	shader_program = glCreateProgram();

	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);

	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(shader_program, 512, nullptr, info_log);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILE FAILED\n" << info_log << "\n\n";
	}

	// Cleanup Unneeded Shaders
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);


	// --- Vertex Data ---
	float vertices[] =
	{
		0.5f, 0.5f, 0.0f,   // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f, // bottom left
		-0.5f, 0.5f, 0.0f   // top left
	};

	unsigned int indices[] =
	{
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	// Setup Vertex Buffer Object
	unsigned int VBO{}, VAO{}, EBO{};
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind Vertex Array first: Must do this first, then Bind and set vertex buffers, and then configure vertex attributes.
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	// Vertex Attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// ------------------------------------------------

	// Main loop
	while (!glfwWindowShouldClose(m_window))
	{
		// Input handling
		m_engine_window.process_input(m_window);

		// Rendering: Clear the Back Buffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw Triangle: On the Back Buffer
		glUseProgram(shader_program);
		glBindVertexArray(VAO);

		// Using the EBO to draw a rectangle
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// Moving to Element Buffer
		// glDrawArrays(GL_TRIANGLES, 0, 3);

		// Swap the Front and Back Buffers
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	return 0;
}