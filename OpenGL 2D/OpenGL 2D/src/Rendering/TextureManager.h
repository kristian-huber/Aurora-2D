#pragma once
#ifndef _H_TEXTUREMANAGER
#define _H_TEXTUREMANAGER

#include <map>
#include <string>
#include <glad/glad.h>
#include "Textures.h"
#include "../Util/VectorMap.h"

namespace TextureManager {
	extern VectorMap<GLuint, std::string> renderLayers;
	extern std::map<std::string, Texture*> textures;
	extern std::map<std::string, Atlas*> atlases;
	extern GLuint vaoID;
	extern GLuint eboID;
	extern GLuint posVBO;
	extern GLuint texVBO;
	extern int STANDARD_TILE_SIZE;

	void initalize();
	void loadAtlas(const std::string& id, GLfloat rows = 1, GLfloat cols = 1);
	void registerTexture(const std::string& id, const std::string& atlas, GLuint layer, GLuint x, GLuint y, GLfloat width, GLfloat height);
	void bindTexture(const std::string& id);
	void unbindTexture();
	void cleanUp();
};

#endif