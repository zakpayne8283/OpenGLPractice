#pragma once

#include "OpenGLLoader.h"

class Shader
{
public:
	unsigned int shader;

	virtual ~Shader() = default;
	virtual bool compile() = 0;

protected:
	int  success;
	char infoLog[512];
};

class VertexShader : public Shader
{
public:

	VertexShader()
	{
		shader = glCreateShader(GL_VERTEX_SHADER);
	}

	bool compile() override
	{
		std::printf("-- Building vertex shader...\n");

		// Set vertex shader source and compile it
		glShaderSource(shader, 1, &DEFAULT_SHADER, NULL);
		glCompileShader(shader);

		// Ensure successful shader compilation
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::printf("-- %s -- %s", "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n", infoLog);
			return false;
		}
		
		std::printf("-- Vertex shader built successfully!\n");

		return true;
	}

private:

	const char* DEFAULT_SHADER =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
};

class FragmentShader : public Shader
{
public:

	FragmentShader()
	{
		// Create the fragment shader
		shader = glCreateShader(GL_FRAGMENT_SHADER);
	}

	bool compile() override
	{
		std::printf("-- Building fragment shader...\n");

		// Set fragment shader source and compile it
		glShaderSource(shader, 1, &DEFAULT_SHADER, NULL);
		glCompileShader(shader);

		// Ensure successful shader compilation
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::printf("-- %s -- %s", "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n", infoLog);
			return false;
		}
		
		std::printf("-- Fragment shader built successfully!\n");

		return true;
	}

private:
	const char* DEFAULT_SHADER =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";
};