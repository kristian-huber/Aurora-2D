#pragma once
#ifndef H_COMBINE_SHADER
#define H_COMBINE_SHADER

#include "src/Rendering/BaseShader.h"
#include <glad/glad.h>

class CombineShader : public BaseShader {
	GLuint u_colorTexture;
	GLuint u_highlightTexture;

public:
	CombineShader();
};


#endif