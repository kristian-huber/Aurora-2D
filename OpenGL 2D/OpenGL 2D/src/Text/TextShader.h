#pragma once
#ifndef _H_TEXT_SHADER
#define _H_TEXT_SHADER

#include "../Rendering/BaseShader.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

class TextShader : public BaseShader {
	GLuint u_projection;
	GLuint u_textColor;
	GLuint u_image;
public:
	TextShader();
	void loadProjectionMatrix(const glm::mat4& proj);
	void loadColor(const glm::vec3& color);
};
#endif