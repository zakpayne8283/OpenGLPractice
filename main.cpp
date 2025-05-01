#include<fstream>

#include "glad/glad.h"

// Basic window for glfw3
#include "Window.h";

int main()
{
	std::printf("Program Started");

	Window::initialize(640, 480, "Window Name");

	return 0;
}