#pragma once

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <string>

class Window {
public:
	Window(std::string name, int w, int h);
	~Window();

	std::string name;
	const int WIDTH;
	const int HEIGHT;

	GLFWwindow* window;

	bool framebufferResized = false;

private:

	static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
		auto app = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
		app->framebufferResized = true;
	}
};