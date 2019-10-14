#include "Window.h"
#include "../Util/InputManager.h"
#include "../Util/Constants.h"
#include <iostream>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// Close application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	// Register keys
	if (key >= 0 && key < 1024){
		if (action == GLFW_PRESS)
			InputManager::KEYS[key] = GL_TRUE;
		else if (action == GLFW_RELEASE)
			InputManager::KEYS[key] = GL_FALSE;
	}
}

void Window::loadWindowSettings() {

	// Tell GLFW the OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, vMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, vMinor);

	// Tell GLFW to get rid of all the backwards compatible features
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Make the window not resizable
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_DECORATED, GL_FALSE);

	// vsync on
	glfwSwapInterval(1);

	// This is needed for Mac
	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif
}

void Window::loadOpenGLSettings() {
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Window::createWindow(int width, int height) {

	// Create the window
	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

	// Check for errors
	if (window == NULL) {
		std::cout << "[Console]: Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(0);
	}

	// Tell OpenGL we want to render to this window
	glfwMakeContextCurrent(window);

	// Initialize GLAD, which takes care of OpenGL pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "[Console]: Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		exit(0);
	}

	// Tell GLFW where to send the key function
	glfwSetKeyCallback(window, key_callback);

	// Don't show the mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set window size
	glViewport(0, 0, width, height);
}

void Window::update() {
	//Check for keyboard and mouse input
	glfwPollEvents();

	glfwGetCursorPos(window, &Constants::mouseX, &Constants::mouseY);

	// Update the pixels on the screen to the new pixels
	glfwSwapBuffers(window);
}

Window::Window(const std::string& t, int width, int height) : title(t) {
	glfwInit();
	loadWindowSettings();
	createWindow(width, height);
	loadOpenGLSettings();
}

Window::~Window() {
	std::cout << "[Console]: Terminated GLFW Window" << std::endl;
	glfwTerminate();
}