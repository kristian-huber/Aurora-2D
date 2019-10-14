#include "ContrastChanger.h"
#include "src/FBO/ContrastShader.h"
#include "src/FBO/ImageRenderer.h"
#include "src/Util/Constants.h"

ContrastChanger::ContrastChanger() {
	shader = new ContrastShader();
	renderer = new ImageRenderer();
}

ContrastChanger::~ContrastChanger() {
	delete shader;
	delete renderer;
}

void ContrastChanger::render(unsigned int texture) {
	shader->start();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	renderer->render();

	shader->stop();
}