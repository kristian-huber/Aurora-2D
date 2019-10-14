#pragma once
#ifndef _H_FBO_SHADER
#define _H_FBO_SHADER

#include "../Rendering/BaseShader.h"
#include <glm/vec2.hpp>
#include <glad/glad.h>

class ContrastShader : public BaseShader {
	GLuint u_screenTexture;
public:
	ContrastShader();
};
#endif