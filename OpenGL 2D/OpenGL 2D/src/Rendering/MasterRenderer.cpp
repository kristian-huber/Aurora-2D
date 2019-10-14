#include "MasterRenderer.h"
#include "../Util/InputManager.h"
#include "../Util/Constants.h"
#include "../../PostProcessing.h"
#include <glfw/glfw3.h>
#include <iostream>

MasterRenderer::MasterRenderer() {
	spriteRenderer = new SpriteRenderer(Constants::projection); 
	guiRenderer = new GUIRenderer(Constants::projection);
	textRenderer = new TextRenderer();

	fbo = new FBO(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT);

	glCullFace(GL_BACK);
}

MasterRenderer::~MasterRenderer() {
	delete spriteRenderer;
	delete guiRenderer;
	delete textRenderer;

	delete fbo;
}

void MasterRenderer::update(GLfloat delta) {
	int speed = 300;
	int bounds = 50;

	if (Constants::mouseY < bounds) {
		cameraPos.y -= delta * speed;
	}else if (Constants::mouseY > Constants::WINDOW_HEIGHT - bounds) {
		cameraPos.y += delta * speed;
	}

	if (Constants::mouseX < bounds) {
		cameraPos.x -= delta * speed;
	}else if (Constants::mouseX > Constants::WINDOW_WIDTH - 2 * bounds) {
		cameraPos.x += delta * speed;
	}

	Constants::camPos = cameraPos;

	viewMatrix[3][0] = -cameraPos.x;
	viewMatrix[3][1] = -cameraPos.y;
}



void MasterRenderer::render(GLfloat delta, World& world, GUIScreen& screen) {
	update(delta);

	// First pass
	fbo->bindFrameBuffer();
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 1);
	spriteRenderer->renderSprites(world.lights, viewMatrix, world.getSprites());
	fbo->unbindFrameBuffer();

	PostProcessing::doPostProcessing(fbo->getColorTexture());

	//Second pass
	guiRenderer->renderGUIs(screen.guis);
	textRenderer->renderTexts(screen.texts);
}