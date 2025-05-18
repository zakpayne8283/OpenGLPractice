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

	// While the window shouldn't close
	while (!glfwWindowShouldClose(Window::getWindow()))
	{
		// ---- Render objects here

		// Clear color buffer
		Window::clearColorBuffer();
		
		// Copies the triangleVertices data into the vertex buffer
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

		// Specifies information about the VBO
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// ---- End render

		// Buffer swap
		glfwSwapBuffers(Window::getWindow());

		// Check for "should close" events
		glfwPollEvents();
	}

	Window::teardown();

	return 0;
}