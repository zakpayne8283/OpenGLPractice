#pragma once

#include<fstream>

#include "OpenGLLoader.h"
#include "Shaders.h"

// TODO: Rename window to something better and more descriptive
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
		std::printf("Starting window initialization...\n");

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
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::printf("ERROR: Failed to initialize GLAD!");
			exit(EXIT_FAILURE);
		}

		// Initialize the shaders
		initializeShaders();

		// Setup viewport
		glViewport(0, 0, windowWidth, windowHeight);

		std::printf("Window successfully initialized!\n");

		return true;
	}

	/// <summary>
	/// Clears the color buffer (it's right there in the name)
	/// </summary>
	static void clearColorBuffer()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);	// Is a "state setting" function
		glClear(GL_COLOR_BUFFER_BIT);			// Is a "state using" function (TODO: separate all state using functions to a seperate function?)
	}

	/// <summary>
	/// Destroy GLFW window properly
	/// </summary>
	/// <param name="ignoreExit">Ignores exit() - used in testing</param>
	static void teardown(bool ignoreExit=false)
	{
		glDeleteProgram(shaderProgram);

		delete vertexShader;
		delete fragmentShader;

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
	
	/// <summary>
	/// Gets the shader program being used by the window
	/// </summary>
	/// <returns></returns>
	static unsigned int getShaderProgram()
	{
		return shaderProgram;
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

	// Vertex array object
	static unsigned int VAO;

	// Vertex buffer object
	static unsigned int VBO;

	// ---- Shaders

	static VertexShader* vertexShader;
	static FragmentShader* fragmentShader;

	static unsigned int shaderProgram;

	// ---- End Shaders

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

	// Window resize callback function
	static void resize_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	// Initialize all shaders
	static void initializeShaders()
	{
		int  success;
		char infoLog[512];

		std::printf("- Initializing shaders...\n");

		// Create the vertex shader
		vertexShader = new VertexShader();
		vertexShader->compile();

		// Create the vertex shader
		fragmentShader = new FragmentShader();
		fragmentShader->compile();

		// TODO: Handle if either shader compile doesn't work

		std::printf("-- Creating shader program...\n");

		// Creates the shader program
		shaderProgram = glCreateProgram();

		// Attach the shaders to the program and link the progarm
		glAttachShader(shaderProgram, vertexShader->shader);
		glAttachShader(shaderProgram, fragmentShader->shader);
		glLinkProgram(shaderProgram);

		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::printf("-- %s -- %s", "ERROR::SHADER::SHADER_PROGRAM::CREATION_FAILED\n", infoLog);
		}
		else
		{
			std::printf("-- Shader program successfully created!\n");
		}

		std::printf("-- Cleaning up created shaders...\n");

		// Clean up created shaders
		glDeleteShader(vertexShader->shader);
		glDeleteShader(fragmentShader->shader);

		std::printf("- Shaders initialized successfully!\n");
	}
};

// ---- Defaults ----

// Window info
int Window::windowWidth = 640;
int Window::windowHeight = 480;
const char* Window::windowTitle = "Title";
GLFWwindow* Window::window = nullptr;

// Buffers
unsigned int Window::VAO;
unsigned int Window::VBO;

// ---- Shaders
VertexShader* Window::vertexShader;
FragmentShader* Window::fragmentShader;

unsigned int Window::shaderProgram;

// ---- End Shaders