#include "Window.h"

Window::Window(int w, int h) : WIDTH{ w }, HEIGHT{ h } {
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "tamcut", nullptr , nullptr);
	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}

Window::~Window() {
	glfwDestroyWindow(window);
	glfwTerminate();
}