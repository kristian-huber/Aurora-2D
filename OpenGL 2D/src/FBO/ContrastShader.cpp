#include "ContrastShader.h"
#include "../Util/Constants.h"

ContrastShader::ContrastShader() : BaseShader("FBOVertShader.txt", "FBOContrast.txt") {
	u_screenTexture = glGetUniformLocation(shaderID, "screenTexture");
	
	this->loadInteger(u_screenTexture, 0);
}