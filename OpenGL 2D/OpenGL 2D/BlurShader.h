#pragma once
#ifndef _H_BLUR_SHADER
#define _H_BLUR_SHADER

#include "src/Rendering/BaseShader.h"
#include <glad/glad.h>

class BlurShader : public BaseShader{
	GLuint u_vertical;
	GLuint u_targetDim;

public:
	BlurShader();
	void loadTargetDimension(int dim);
	void loadVertical(bool vertical);
};

#endif