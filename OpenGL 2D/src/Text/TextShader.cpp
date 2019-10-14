#include "TextShader.h"

TextShader::TextShader() : BaseShader("TextVert.txt", "TextFrag.txt") {
	u_projection = glGetUniformLocation(shaderID, "projection");
	u_textColor = glGetUniformLocation(shaderID, "textColor");
	u_image = glGetUniformLocation(shaderID, "text");

	//Connect the texture
	this->loadInteger(u_image, 0);
}
void TextShader::loadProjectionMatrix(const glm::mat4& proj) {
	this->loadMatrix4f(u_projection, proj);
}
void TextShader::loadColor(const glm::vec3& color) {
	this->loadVector3f(u_textColor, color);
}