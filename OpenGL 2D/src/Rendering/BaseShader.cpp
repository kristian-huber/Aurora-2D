#include <stdio.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "BaseShader.h"

int BaseShader::loadShader(const std::string& file, GLuint ID) {
	// Read the shader code from the file
	std::string shaderCode;
	std::ifstream shaderStr(file, std::ios::in);
	if (shaderStr.is_open()) {
		std::stringstream sstr;
		sstr << shaderStr.rdbuf();
		shaderCode = sstr.str();
		shaderStr.close();
	} else {
		std::cout << "[ERROR]: Cannot Find File: " << file << std::endl;
		getchar();
		return 0;
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Shader
	std::cout << "[Console]: Compiling shader : " << file << std::endl;
	char const* srcPtr = shaderCode.c_str();
	glShaderSource(ID, 1, &srcPtr, NULL);
	glCompileShader(ID);

	// Check Shader Output
	glGetShaderiv(ID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> errorMsg(InfoLogLength + 1);
		glGetShaderInfoLog(ID, InfoLogLength, NULL, &errorMsg[0]);
		printf("%s\n", &errorMsg[0]);
	}

	return 1;
}

BaseShader::BaseShader(const std::string& vertFile, const std::string& fragFile) {

	// Create the shaders
	GLuint vertexID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentID = glCreateShader(GL_FRAGMENT_SHADER);

	int r1 = loadShader("Shaders/" + vertFile, vertexID);
	int r2 = loadShader("Shaders/" + fragFile, fragmentID);
	if (r1 && r2 == 0){
		printf("[ERROR]: Could not create shader\n");
		return;
	}

	// Link the program
	printf("[Console]: Linking programs\n");
	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexID);
	glAttachShader(programID, fragmentID);
	glLinkProgram(programID);

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Check the program
	glGetProgramiv(programID, GL_LINK_STATUS, &Result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(programID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDetachShader(programID, vertexID);
	glDetachShader(programID, fragmentID);

	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);

	shaderID = programID;
}

void BaseShader::loadBoolean(GLuint location, GLboolean value) {
	glUniform1i(location, value ? 1 : 0);
}

void BaseShader::loadFloat(GLuint location, GLfloat value){
	glUniform1f(location, value);
}
void BaseShader::loadInteger(GLuint location, GLint value){
	glUniform1i(location, value);
}
void BaseShader::loadVector2f(GLuint location, GLfloat x, GLfloat y){
	glUniform2f(location, x, y);
}
void BaseShader::loadVector2f(GLuint location, const glm::vec2 &value){
	glUniform2f(location, value.x, value.y);
}
void BaseShader::loadVector3f(GLuint location, GLfloat x, GLfloat y, GLfloat z){
	glUniform3f(location, x, y, z);
}
void BaseShader::loadVector3f(GLuint location, const glm::vec3 &value){
	glUniform3f(location, value.x, value.y, value.z);
}
void BaseShader::loadVector4f(GLuint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w){
	glUniform4f(location, x, y, z, w);
}
void BaseShader::loadVector4f(GLuint location, const glm::vec4 &value){
	glUniform4f(location, value.x, value.y, value.z, value.w);
}
void BaseShader::loadMatrix4f(GLuint location, const glm::mat4 &matrix){
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}