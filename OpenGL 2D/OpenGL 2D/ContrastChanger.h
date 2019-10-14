#pragma once
#ifndef _H_CONTRAST_CHANGER
#define _H_CONTRAST_CHANGER

class ImageRenderer;
class ContrastShader;

class ContrastChanger {
	ImageRenderer* renderer;
	ContrastShader* shader;

public:
	ContrastChanger();
	~ContrastChanger();
	void render(unsigned int texture);
};

#endif