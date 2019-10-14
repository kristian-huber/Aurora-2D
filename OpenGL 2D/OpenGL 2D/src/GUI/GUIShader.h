#pragma once
#ifndef _GUI_SHADER
#define _GUI_SHADER

#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include "../Rendering/BaseShader.h"

class GUIShader : public BaseShader{
	GLuint u_model;
	GLuint u_projection;
	GLuint u_image;
	GLuint u_offset;
	GLuint u_rows;
	GLuint u_cols;

public:
	GUIShader();
	void loadModelMatrix(const glm::mat4& model);
	void loadProjectionMatrix(const glm::mat4& projection);
	void loadOffset(float x, float y);
	void loadRows(float rows);
	void loadCols(float cols);
};

#endif