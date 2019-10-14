#pragma once
#ifndef _H_GAUSSIAN_BLUR
#define _H_GAUSSIAN_BLUR

#include "src/FBO/ImageRenderer.h"

class BlurShader;

class GaussianBlur {
	ImageRenderer* renderer;
	BlurShader* shader;
public:
	GaussianBlur(bool vertical, int targetFBOWidth, int targetFBOHeight);
	~GaussianBlur();
	void render(int texture);
	unsigned int getTexture() { return renderer->getOutputTexture(); }
};

#endif