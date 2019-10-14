#pragma once
#ifndef _H_TEXT_RENDERER
#define _H_TEXT_RENDERER

#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>
#include "../Util/Constants.h"
#include "TextShader.h"
#include "Text.h"

class TextRenderer {
	//This means the bottom left is (0,0)
	glm::mat4 projection = glm::ortho(0.0f, (float)Constants::WINDOW_HEIGHT, 0.0f, (float)Constants::WINDOW_HEIGHT);

	TextShader* shader;

	GLuint VAO, VBO;

	void renderText(const std::string& text, GLfloat x, GLfloat y, GLfloat scale, const glm::vec3& color);
public:
	TextRenderer();
	~TextRenderer();
	void renderTexts(const std::vector<Text>& texts);
};

#endif