#include "BrightFilter.h"
#include "BrightFilterShader.h"

BrightFilter::BrightFilter(int width, int height) {
	shader = new BrightFilterShader();
	renderer = new ImageRenderer(width, height);
}

BrightFilter::~BrightFilter() {
	delete shader;
	delete renderer;
}

void BrightFilter::render(int texture) {
	shader->start();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	renderer->render();

	shader->stop();
}