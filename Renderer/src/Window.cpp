#include "Window.h"

Window::Window(int w, int h) : WIDTH{ w }, HEIGHT{ h } {
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	window = glfwCreateWindow(WIDTH, HEIGHT, "tamcut", nullptr, nullptr);
	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}

Window::~Window() {
	glfwDestroyWindow(window);
	glfwTerminate();
}