#include "ModelManager.h"
#include <iostream>

namespace ModelManager{
	GLuint quadVAO = 0;
	GLuint quadSize = 0;

	std::vector<GLuint> VBOs = std::vector<GLuint>();

	void initalize() {
		GLfloat positions[] = {
			1, 1, // top right
			1, 0, // bottom right
			0, 0,  // bottom left

			0, 1,  // top left
			1, 1, // top right
			0, 0,  // bottom left
		};
		GLfloat textureCoords[] = {
			1.0f, 1.0f,  // lower-left corner  
			1.0f, 0.0f,  // lower-right corner
			0.0f, 0.0f,   // top-center corner

			0.0f, 1.0f,
			1.0f, 1.0f,  
			0.0f, 0.0f
		};

		quadSize = 6;
		quadVAO = loadToVAO(positions, sizeof(positions), textureCoords, sizeof(textureCoords));
	}

	void cleanUp() {
		glDeleteVertexArrays(1, &quadVAO);

		for (const GLuint& i : VBOs) {
			glDeleteBuffers(1, &i);
		}
	}

	GLuint createVAO() {
		GLuint vaoID;
		glGenVertexArrays(1, &vaoID);
		glBindVertexArray(vaoID);
		return vaoID;
	}
	void storeDataInAttributeList(int attributeNumber, int coordinateSize, const float* data, int size) {
		GLuint vboID;
		glGenBuffers(1, &vboID);

		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, GL_FALSE, coordinateSize * sizeof(GLfloat), (GLvoid*)0);
	
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		VBOs.push_back(vboID);
	}

	GLuint loadToVAO(const std::vector<GLfloat>& positions, const std::vector<GLfloat>& textureCoords) {
		return loadToVAO(&positions[0], positions.size() * sizeof(GLfloat), &textureCoords[0], textureCoords.size() * sizeof(GLfloat));
	}

	GLuint loadToVAO(const float* positions, int posSize, const float* textureCoords, int texSize) {
		GLuint vaoID = createVAO();

		for (int i = 0; i < posSize / 4; i++) {
			std::cout << positions[i] << "|";
		}
		std::cout << '/b' << std::endl;

		storeDataInAttributeList(0, 2, positions, posSize);
		storeDataInAttributeList(1, 2, textureCoords, texSize);

		glBindVertexArray(0);

		return vaoID;
	}

	GLuint loadToVAO(const float* positions, int posSize) {
		GLuint vaoID = createVAO();

		storeDataInAttributeList(0, 2, positions, posSize);

		glBindVertexArray(0);

		return vaoID;
	}
}