#include<fstream>

// Basic window for glfw3
#include "Window.h";

// All OpenGL stuff
#include "OpenGLLoader.h"

// All shapes to include
// #include "Triangle.h"

int main()
{
	std::printf("Program Started");

	Window::initialize(800, 600, "OpenGL Practice");

	GLfloat triangleVerticies[3][2] =
	{
		{ -0.90, -0.90 },
		{ 0.85, -0.90 },
		{ -0.90,  0.85 }
	};

	// Triangle* triangle = new Triangle(triangleVerticies);

	// While the window shouldn't close
	while (!glfwWindowShouldClose(Window::getWindow()))
	{
		// Render objects here

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// End render

		// Buffer swap
		glfwSwapBuffers(Window::getWindow());

		// Check for "should close" events
		glfwPollEvents();
	}

	Window::teardown();

	return 0;
}