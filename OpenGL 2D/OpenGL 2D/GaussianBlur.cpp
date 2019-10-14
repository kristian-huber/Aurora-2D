#include "GuassianBlur.h"
#include "BlurShader.h"
#include <glad/glad.h>

GaussianBlur::GaussianBlur(bool vertical, int targetFBOWidth, int targetFBOHeight) {
	shader = new BlurShader();
	renderer = new ImageRenderer(targetFBOWidth, targetFBOHeight);
	shader->start();
	shader->loadVertical(vertical);
	shader->loadTargetDimension(vertical ? targetFBOHeight : targetFBOWidth);
	shader->stop();
}

GaussianBlur::~GaussianBlur() {
	delete shader;
	delete renderer;
}

void GaussianBlur::render(int texture) {
	shader->start();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	renderer->render();

	shader->stop();
}