#pragma once
#ifndef _H_MODEL_MANAGER
#define _H_MODEL_MANAGER

#include <map>
#include <string>
#include <vector>
#include <glad/glad.h>

namespace ModelManager {
	extern GLuint quadVAO;
	extern GLuint quadSize;
	
	extern std::vector<GLuint> VBOs;

	GLuint createVAO();

	void storeDataInAttributeList(int attributeNumber, int coordinateSize, float* data, int size);

	GLuint loadToVAO(const std::vector<GLfloat>& positions, const std::vector<GLfloat>& textureCoords);
	GLuint loadToVAO(const float* positions, int posSize, const float* textureCoords, int texSize);
	GLuint loadToVAO(const float* positions, int posSize);

	inline void deleteVAO(GLuint id) {
		glDeleteVertexArrays(1, &id);
	}

	void initalize();
	void cleanUp();
}

#endif