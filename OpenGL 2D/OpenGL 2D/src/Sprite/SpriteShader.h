#pragma once
#ifndef _H_SPRITESHADER
#define _H_SPRITESHADER

#include "../Rendering/BaseShader.h"
#include "Light.h"
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class SpriteShader: public BaseShader{
	glm::vec4 defaultVec = glm::vec4(0.0);

	GLuint u_model;
	GLuint u_color;
	GLuint u_view;
	GLuint u_projection;
	GLuint u_image;
	GLuint u_offset;
	GLuint u_rows;
	GLuint u_cols;
	GLuint u_ambientLight;
	GLuint u_bounding;
	GLuint u_centerPoint;
	GLuint u_boundingRadius;
	GLuint u_lightPos[16];
	GLuint u_lightCol[16];
	GLuint u_radius[16];

public:
	SpriteShader();
	void loadModelMatrix(const glm::mat4& model);
	void loadSpriteColor(GLfloat r, GLfloat b, GLfloat g);
	void loadViewMatrix(const glm::mat4& view);
	void loadProjectionMatrix(const glm::mat4& projection);
	void loadOffset(GLfloat x, GLfloat y);
	void loadRows(GLfloat rows);
	void loadCols(GLfloat cols);
	void loadAmbientLight(GLfloat brightness);
	void loadLight(int i, const Light& lights);
	void loadLight(int i);
	void loadRenderBounding(int toRender);
	void loadCircleBounds(float cx, float cy, float rad);
};

#endif