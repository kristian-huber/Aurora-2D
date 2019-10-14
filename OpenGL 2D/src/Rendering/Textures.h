#pragma once
#ifndef _H_TEXTURE
#define _H_TEXTURE

#include <glad/glad.h>
#include <string>

struct Atlas {
	GLuint atlasID;
	GLfloat rows, cols;

	Atlas(GLuint id, GLfloat r, GLfloat c) : atlasID(id), rows(r), cols(c) {}
};

struct Texture {
	std::string atlas;
	GLuint x, y, width, height, layer;

	Texture(const std::string& atlas, GLuint layer, GLuint xPos, GLuint yPos, GLfloat w, GLfloat h) : atlas(atlas), layer(layer), x(xPos), y(yPos), width(w), height(h) {}
};

#endif