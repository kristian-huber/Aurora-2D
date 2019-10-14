#include "GUIShader.h"

GUIShader::GUIShader() : BaseShader("GUIVert.txt", "GUIFrag.txt") {
	GUIShader::u_model = glGetUniformLocation(shaderID, "model");
	GUIShader::u_projection = glGetUniformLocation(shaderID, "projection");
	GUIShader::u_image = glGetUniformLocation(shaderID, "image");
	GUIShader::u_offset = glGetUniformLocation(shaderID, "offset");
	GUIShader::u_rows = glGetUniformLocation(shaderID, "rows");
	GUIShader::u_cols = glGetUniformLocation(shaderID, "cols");

	//Connect the texture
	this->loadInteger(u_image, 0);
}

void GUIShader::loadModelMatrix(const glm::mat4& model) {
	this->loadMatrix4f(u_model, model);
}

void GUIShader::loadProjectionMatrix(const glm::mat4& projection) {
	this->loadMatrix4f(u_projection, projection);
}

void GUIShader::loadOffset(GLfloat x, GLfloat y) {
	this->loadVector2f(u_offset, x, y);
}

void GUIShader::loadRows(GLfloat rows) {
	this->loadFloat(u_rows, rows);
}
void GUIShader::loadCols(GLfloat cols) {
	this->loadFloat(u_cols, cols);
}
