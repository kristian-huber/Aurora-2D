#pragma once
#ifndef _H_COMBINE_SHADER
#define _H_COMBINE_SHADER

#include "src/FBO/ImageRenderer.h"

class CombineShader;

class CombineFilter {
	ImageRenderer* renderer;
	CombineShader* shader;
public:
	CombineFilter();
	~CombineFilter();
	void render(int colorTexture, int highlightTexture);
	unsigned int getTexture() { return renderer->getOutputTexture(); }
};

#endif