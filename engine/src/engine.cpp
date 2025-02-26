#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <array>

#include "engine.hpp"

#pragma region Shaders
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

#pragma endregion Shaders

void engine::Engine::init()
{
}

int engine::Engine::start()
{
	// -- Windowing --
	m_engine_window.init();

	m_window = m_engine_window.getGLFWwindow();

	if (!m_window)
	{
		return -1;
	}


#pragma region Shading
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

#pragma endregion Shading

#pragma region Verticies and Indices
	// --- Vertex Data ---
	float vertices[] =
	{
		// Triangle One
		-0.75f, 0.25f, 0.0f,		// top
		-0.9f, -0.25f, 0.0f,		// Left
		-0.6f, -0.25f, 0.0f,		// Right

		// Triangle two
		0.75f, 0.25f, 0.0f,		// top
		0.6f, -0.25f, 0.0f,		// left
		0.9f, -0.25f, 0.0f		// right
	};


	// --- Vertex Data ---
	float first_triangle[] =
	{
		-0.75f, 0.25f, 0.0f,		// top
		-0.9f, -0.25f, 0.0f,		// Left
		-0.6f, -0.25f, 0.0f,		// Right
	};

	float second_triangle[] =
	{
		0.75f, 0.25f, 0.0f,		// top
		0.6f, -0.25f, 0.0f,		// left
		0.9f, -0.25f, 0.0f		// right

	};

	unsigned int indices[] =
	{
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
#pragma endregion Verticies and Indices

#pragma region Vertex_Array_and_Buffers

	// Setup Vertex Buffer Object
	GLuint VBOs[2];
	GLuint VAOs[2];

	// Generate Buffers
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);

	// Loop over the array
	for (int i = 0; i < 2; i++)
	{
		glBindVertexArray(VAOs[i]);
		glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) / 2, &vertices[i * 9], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // Because the data is Tightly packed, We can let OpenGL figure it out.
		glEnableVertexAttribArray(0);
	}

#pragma endregion Vertex_Array_and_Buffers


	// Main loop
	// ---------
	while (!glfwWindowShouldClose(m_window))
	{
		// Input handling
		m_engine_window.process_input(m_window);

		// Rendering: Clear the Back Buffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw Triangle: On the Back Buffer
		glUseProgram(shader_program);
		for (int i = 0; i < 2; i++)
		{
			glBindVertexArray(VAOs[i]);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}

		// Moving to Element Buffer, No longer needed

		// Swap the Front and Back Buffers
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	return 0;
}