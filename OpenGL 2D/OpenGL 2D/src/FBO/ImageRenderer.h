#pragma once
#ifndef _H_FBO_RENDERER
#define _H_FBO_RENDERER

#include "FBO.h"

class ImageRenderer {
	FBO* fbo;

public:
	
	//Use this one if you want to render to another FBO
	ImageRenderer(int width, int height);

	//Use this one if you don't want to render to another one
	ImageRenderer() {}

	~ImageRenderer();
	void render();
	unsigned int getOutputTexture() { return fbo->getColorTexture(); }
};

#endif