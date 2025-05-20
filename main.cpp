#include<fstream>

// Basic window for glfw3
#include "Window.h";

// All OpenGL stuff
#include "OpenGLLoader.h"

// All shapes to include
// #include "Triangle.h"

int main()
{
	std::printf("Program Started\n\n");

	Window::initialize(800, 600, "OpenGL Practice");

	float triangleVertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	// TODO: Move vertex array object and vertex buffer objects into an OOP system?
	unsigned int VAO, VBO;

	// Initialize the VAO
	glGenVertexArrays(1, &VAO);

	// Initialize the VBO
	glGenBuffers(1, &VBO);
	
	// Bind VAO, then bind and set VBO(s)
	glBindVertexArray(VAO);
	// Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	// bind the vertex buffer
	// Copies the triangleVertices data into the vertex buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

	// Specifies information about the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(Window::getWindow()))
	{
		// input
		// -----

		// ---- Render objects here

		// Clear color buffer
		Window::clearColorBuffer();
		
		// Set the shader
		glUseProgram(Window::getShaderProgram());

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		

		// ---- End render

		// Buffer swap
		glfwSwapBuffers(Window::getWindow());

		// Check for "should close" events
		glfwPollEvents();
	}

	Window::teardown();

	return 0;
}