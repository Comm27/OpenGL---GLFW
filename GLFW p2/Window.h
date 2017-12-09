#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include "Shader.h"
#include "Texture2D.h"

enum class Window_Error
{
	WIN_OK,
	GLFW_INIT_FAIL,
	GLAD_INIT_FAIL,
	WINDOW_FAIL
};

class Window
{
private:
	GLFWwindow *m_window;
	int m_width, m_height;
	const char *m_title;

private:
	static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
	Window_Error Init();
	void ProcessInput();

public:
	Window(int width, int height, const char *title);
	~Window();
	void Update();
};