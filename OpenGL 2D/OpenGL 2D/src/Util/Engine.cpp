#include "Engine.h"
#include "../Rendering/Window.h"
#include "Constants.h"
#include "../Rendering/MasterRenderer.h"
#include "../Rendering/ModelManager.h"
#include "../Rendering/TextureManager.h"
#include "../../PostProcessing.h"
#include "../../AudioManager2.h"
#include <iostream>

Engine::~Engine() {
	delete renderer;
}

void Engine::start(const std::string& windowName) {
	Window window = Window(windowName, Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT);
	renderer = new MasterRenderer();
	ModelManager::initalize();
	PostProcessing::initialize();
	AudioManager2::initialize();

	loadResources();

	initialize();

	std::cout << "[Console]: Finished Initalizing" << std::endl << std::endl;

	// Game loop variables
	float lastSecondTime = (float)glfwGetTime();
	float previousTime = (float)glfwGetTime();
	int frames = 0;

	// Game loop
	while (!glfwWindowShouldClose(window.getWindow())) {

		// Calculate FPS stuff
		float currentTime = (float)glfwGetTime();
		delta = currentTime - previousTime;
		previousTime = currentTime;
		frames++;
		Constants::ticks++;
		if (currentTime - lastSecondTime >= 1.0) {
			//std::cout << frames << std::endl;
			frames = 0;
			lastSecondTime = currentTime;
			Constants::seconds++;
		}

		Constants::delta = delta;

		// Update and render stuff
		window.update();

		this->loop();
	}

	//Clean up resources and memory
	ModelManager::cleanUp();
	TextureManager::cleanUp();
	PostProcessing::cleanUp();
	AudioManager2::cleanUp();
}