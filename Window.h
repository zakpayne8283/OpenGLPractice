#pragma once

#include "OpenGLLoader.h"

class Window
{
public:
	// Static only class
	Window() = delete;
	
	/// <summary>
	/// Initialize the GLFW Window
	/// </summary>
	/// <param name="width">Width of window</param>
	/// <param name="height">Height of window</param>
	/// <param name="title">Title of window</param>
	/// <returns>True/false window was created</returns>
	static bool initialize(int width=640, int height=480, const char* title = "Title")
	{
		// TODO: Break out the different initialization steps into their own things
		// e.g. initShaders, initBuffers, etc.

		windowWidth = width;
		windowHeight = height;
		windowTitle = title;

		// Setup the error callback function
		glfwSetErrorCallback(error_callback);

		// Try to init GLFW, exit on failure
		if (!glfwInit())
			exit(EXIT_FAILURE);

		// Setup Window Hints
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VERSION);		// Required OpenGL version minimum
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VERSION);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);			// Default core
	
		// Try to create window
		window = glfwCreateWindow(windowWidth, windowHeight, windowTitle, NULL, NULL);
		if (!window)
		{
			// Exit on failure (window is NULL on failure)
			glfwTerminate();
			exit(EXIT_FAILURE);
		}

		// Key callbacks - used for input
		glfwSetKeyCallback(window, key_callback);
		// Resize callback - used on window resize
		glfwSetFramebufferSizeCallback(window, resize_callback);

		// Sets the context for OpenGL to draw
		glfwMakeContextCurrent(window);
		
		// Now initialize GL
		gladLoadGL();

		// Setup viewport
		glViewport(0, 0, windowWidth, windowHeight);

		return true;
	}

	/// <summary>
	/// Destroy GLFW window properly
	/// </summary>
	/// <param name="ignoreExit">Ignores exit() - used in testing</param>
	static void teardown(bool ignoreExit=false)
	{
		// Destroy window
		glfwDestroyWindow(window);

		// Terminate GLFW
		glfwTerminate();

		// Exit, with success code
		if (!ignoreExit)
			exit(EXIT_SUCCESS);
	}

	/// <summary>
	/// Returns the window ptr for usage
	/// TODO: Handle window being nullptr
	/// </summary>
	/// <returns>GLFWwindow*</returns>
	static GLFWwindow* getWindow()
	{
		return window;
	}

private:
	// Window constants
	static const int OPENGL_MAJOR_VERSION = 3;	// Minimum OpenGL version to run
	static const int OPENGL_MINOR_VERSION = 3;

	static const int DEFAULT_EXIT_KEY = GLFW_KEY_ESCAPE;

	// Window setup info
	static int windowWidth;
	static int windowHeight;
	static const char* windowTitle;

	// The actual window
	static GLFWwindow* window;

	// Error callback function for GLFW to print errors
	static void error_callback(int error, const char* description)
	{
		fprintf(stderr, "Error %d: %s\n", error, description);
	}

	// Key callback function for GLFW that catches user input
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	static void resize_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
};

// ---- Defaults ----

// Window info
int Window::windowWidth = 640;
int Window::windowHeight = 480;
const char* Window::windowTitle = "Title";
GLFWwindow* Window::window = nullptr;
