#include "ImageRenderer.h"
#include "../Rendering/ModelManager.h"
#include <iostream>

ImageRenderer::ImageRenderer(int width, int height) {
	fbo = new FBO(width, height);
}

ImageRenderer::~ImageRenderer() {
	delete fbo;
}

void ImageRenderer::render() {
	if (fbo != nullptr) {
		fbo->bindFrameBuffer();
	}

	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 1);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	if (fbo != nullptr) {
		fbo->unbindFrameBuffer();
	}
}