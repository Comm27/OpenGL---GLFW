#include "Window.h"

Window::Window(int width, int height, const char * title)
	: m_window(nullptr), m_width(width), m_height(height)
{
	m_title = title;
	std::cout << "Width: " << m_width << std::endl;
	std::cout << "Height: " << m_height << std::endl;
	std::cout << "Title: " << m_title << std::endl;

	Window_Error win_error = Init();

	//Logger(win_error);
}

Window::~Window()
{
	glfwTerminate();
}


void Window::framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
}

Window_Error Window::Init()
{
	if (!glfwInit())
	{
		return Window_Error::GLFW_INIT_FAIL;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	m_window = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr);

	if (m_window == nullptr)
	{
		glfwTerminate();
		return Window_Error::WINDOW_FAIL;
	}

	glfwMakeContextCurrent(m_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return Window_Error::GLAD_INIT_FAIL;
	}

	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

	return Window_Error::WIN_OK;
}

void Window::ProcessInput()
{
	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(m_window, true);
	}
}

void Window::Update()
{
	while (!glfwWindowShouldClose(m_window))
	{
		ProcessInput();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}
}