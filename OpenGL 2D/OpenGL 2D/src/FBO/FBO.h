#pragma once
#ifndef _H_FBO
#define _H_FBO

class FBO {
	unsigned int frameBuffer, colorBuffer, colorTexture;
	int width, height;

public:
	FBO(int width, int height);
	~FBO();

	void bindFrameBuffer();
	void unbindFrameBuffer();
	void bindToRead();
	unsigned int getColorTexture() { return colorTexture; }
};

#endif