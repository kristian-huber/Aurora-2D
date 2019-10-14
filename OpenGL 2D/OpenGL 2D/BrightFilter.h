#pragma once
#ifndef _H_BRIGHT_FILTER
#define _H_BRIGHT_FILTER

#include "src/FBO/ImageRenderer.h"

class BrightFilterShader;

class BrightFilter {
	ImageRenderer* renderer;
	BrightFilterShader* shader;
public:
	BrightFilter(int width, int height);
	~BrightFilter();
	void render(int texture);
	unsigned int getTexture() { return renderer->getOutputTexture(); }
};

#endif