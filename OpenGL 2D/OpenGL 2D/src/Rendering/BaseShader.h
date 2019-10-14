#pragma once
#ifndef _H_SHADER
#define _H_SHADER

#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <string>

class BaseShader {
	int loadShader(const std::string& file, GLuint ID);
protected:
	GLuint shaderID;

	void loadBoolean(GLuint location, GLboolean value);
	void loadFloat(GLuint location, GLfloat value);
	void loadInteger(GLuint location, GLint value);
	void loadVector2f(GLuint location, GLfloat x, GLfloat y);
	void loadVector2f(GLuint location, const glm::vec2 &value);
	void loadVector3f(GLuint location, GLfloat x, GLfloat y, GLfloat z);
	void loadVector3f(GLuint location, const glm::vec3 &value);
	void loadVector4f(GLuint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	void loadVector4f(GLuint location, const glm::vec4 &value);
	void loadMatrix4f(GLuint location, const glm::mat4 &matrix);
public:
	BaseShader(const std::string& vertFile, const std::string& fragFile);
	void start(){ glUseProgram(shaderID); }
	void stop() { glUseProgram(0); }
};

#endif