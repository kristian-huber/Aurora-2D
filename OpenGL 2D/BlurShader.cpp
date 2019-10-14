#include "BlurShader.h"

BlurShader::BlurShader() : BaseShader("FBOBlurVert.txt", "FBOBlurFrag.txt") {
	u_vertical = glGetUniformLocation(shaderID, "vertical");
	u_targetDim = glGetUniformLocation(shaderID, "targetDim");

	GLuint texture = glGetUniformLocation(shaderID, "originalTexture");
}

void BlurShader::loadTargetDimension(int dim) {
	loadFloat(u_targetDim, dim);
}

void BlurShader::loadVertical(bool vertical) {
	loadBoolean(u_vertical, vertical);
}