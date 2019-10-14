#include "FBO.h"
#include "../Util/Constants.h"
#include <glad/glad.h>
#include <iostream>

FBO::FBO(int width, int height) {
	this->width = width;
	this->height = height;

	//Create Framebuffer
	glGenFramebuffers(1, &frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);

	//Create texture attachment
	glGenTextures(1, &colorTexture);
	glBindTexture(GL_TEXTURE_2D, colorTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);

	/*The buffer isn't 'complete' unless:
		1.) Attach at least one buffer (color, depth, stencil)
		2.) At least one color attachmnt
		3.) All attachements should be complete (reserved memory)
		4.) Same number of samples
	 So we check it with:
	*/
	auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "[ERROR]: Framebuffer not complete: " << fboStatus << std::endl;

	unbindFrameBuffer();
}

FBO::~FBO() {
	glDeleteFramebuffers(1, &frameBuffer);
	glDeleteTextures(1, &colorTexture);
	glDeleteRenderbuffers(1, &colorBuffer);
}

void FBO::bindFrameBuffer() {
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBuffer);
	glViewport(0, 0, width, height);
}

void FBO::unbindFrameBuffer() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT);
}

void FBO::bindToRead() {
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, frameBuffer);
	glReadBuffer(GL_COLOR_ATTACHMENT0);
}