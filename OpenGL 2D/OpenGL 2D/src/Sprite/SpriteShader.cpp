#include "SpriteShader.h"
#include <string>

SpriteShader::SpriteShader() : BaseShader("VertexShader.txt", "FragmentShader.txt") {
	SpriteShader::u_model = glGetUniformLocation(shaderID, "model");
	SpriteShader::u_color = glGetUniformLocation(shaderID, "spriteColor");
	SpriteShader::u_view = glGetUniformLocation(shaderID, "view");
	SpriteShader::u_image = glGetUniformLocation(shaderID, "image");
	SpriteShader::u_offset = glGetUniformLocation(shaderID, "offset");
	SpriteShader::u_rows = glGetUniformLocation(shaderID, "rows");
	SpriteShader::u_cols = glGetUniformLocation(shaderID, "cols");
	SpriteShader::u_projection = glGetUniformLocation(shaderID, "projection");
	SpriteShader::u_ambientLight = glGetUniformLocation(shaderID, "ambientLight");
	SpriteShader::u_bounding = glGetUniformLocation(shaderID, "renderBox");
	SpriteShader::u_centerPoint = glGetUniformLocation(shaderID, "centerPoint");
	SpriteShader::u_boundingRadius = glGetUniformLocation(shaderID, "boundingRadius");

	for (int i = 0; i < 16; i++) {
		SpriteShader::u_lightCol[i] = glGetUniformLocation(shaderID, ("lightCol[" + std::to_string(i) + "]").c_str());
		SpriteShader::u_lightPos[i] = glGetUniformLocation(shaderID, ("lightPos[" + std::to_string(i) + "]").c_str());
		SpriteShader::u_radius[i] = glGetUniformLocation(shaderID, ("radius[" + std::to_string(i) + "]").c_str());
	}

	//Connect the texture
	this->loadInteger(u_image, 0);
}

void SpriteShader::loadModelMatrix(const glm::mat4& model) {
	this->loadMatrix4f(u_model, model);
}

void SpriteShader::loadSpriteColor(GLfloat r, GLfloat g, GLfloat b) {
	this->loadVector3f(u_color, r, g, b);
}

void SpriteShader::loadViewMatrix(const glm::mat4& view) {
	this->loadMatrix4f(u_view, view);
}

void SpriteShader::loadProjectionMatrix(const glm::mat4& projection) {
	this->loadMatrix4f(u_projection, projection);
}

void SpriteShader::loadOffset(GLfloat x, GLfloat y) {
	this->loadVector2f(u_offset, x, y);
}

void SpriteShader::loadRows(GLfloat rows) {
	this->loadFloat(u_rows, rows);
}
void SpriteShader::loadCols(GLfloat cols) {
	this->loadFloat(u_cols, cols);
}

void SpriteShader::loadAmbientLight (GLfloat brightness) {
	this->loadFloat(u_ambientLight, brightness);
}

void SpriteShader::loadLight(int i, const Light& light) {
	this->loadVector4f(u_lightCol[i], light.color);
	this->loadVector2f(u_lightPos[i], light.position);
	this->loadFloat(u_radius[i], light.radius);
}

void SpriteShader::loadLight(int i) {
	this->loadVector4f(u_lightCol[i], defaultVec);
	this->loadVector2f(u_lightPos[i], defaultVec);
	this->loadFloat(u_radius[i], 0);
}

void SpriteShader::loadRenderBounding(int toRender) {
	this->loadInteger(u_bounding, toRender);
}

void SpriteShader::loadCircleBounds(float cx, float cy, float rad) {
	this->loadVector2f(u_centerPoint, cx, cy);
	this->loadFloat(u_boundingRadius, rad);
}