#include "CombineShader.h"

CombineShader::CombineShader() : BaseShader("FBOVertShader.txt", "FBOCombineFrag.txt") {
	u_colorTexture = glGetUniformLocation(shaderID, "colorTexture");
	u_highlightTexture = glGetUniformLocation(shaderID, "highlightTexture");

	loadInteger(u_colorTexture, 0);
	loadInteger(u_highlightTexture, 1);
}