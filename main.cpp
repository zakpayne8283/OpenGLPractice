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

	float rectangleVertices[] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};

	unsigned int rectangleIndices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	// TODO: Move vertex array object, vertex buffer objects, and element buffer objects into an OOP system? 
	unsigned int VAO, VBO, EBO;

	// Initialize the VAO
	glGenVertexArrays(1, &VAO);

	// Initialize the VBO
	glGenBuffers(1, &VBO);

	// Initialize the EBO
	glGenBuffers(1, &EBO);
	
	// Bind VAO, then bind and set VBO(s)
	glBindVertexArray(VAO);
	// Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	// bind the vertex buffer
	// Copies the triangleVertices data into the vertex buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), rectangleVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectangleIndices), rectangleIndices, GL_STATIC_DRAW);

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

		// Bind VAO
		glBindVertexArray(VAO);

		// Draw single triangle
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		// Draw single rectangle
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		

		// ---- End render

		// Buffer swap
		glfwSwapBuffers(Window::getWindow());

		// Check for "should close" events
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	Window::teardown();

	return 0;
}