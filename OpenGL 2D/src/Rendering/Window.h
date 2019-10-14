#pragma once
#ifndef _WINDOW_H
#define _WINDOW_H

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
	const int vMajor = 3, vMinor = 3;
	std::string title;

	GLFWwindow* window;

	void loadWindowSettings();
	void loadOpenGLSettings();
	void createWindow(int width, int height);
public:
	Window(const std::string& t, int width, int height);
	~Window();

	void update();
	GLFWwindow* getWindow() { return window; }
};

#endif