#include "TextureManager.h"

#include <string>
#include <iostream>
#include <SOIL2/SOIL2.h>

namespace TextureManager {
	VectorMap<GLuint, std::string> renderLayers = VectorMap<GLuint, std::string>();
	std::map<std::string, Texture*> textures = std::map<std::string, Texture*>();
	std::map<std::string, Atlas*> atlases = std::map<std::string, Atlas*>();
	int STANDARD_TILE_SIZE = 64;

	void loadAtlas(const std::string& id, GLfloat rows, GLfloat cols) {
		//Create a texture
		GLuint texture;
		glGenTextures(1, &texture);

		glBindTexture(GL_TEXTURE_2D, texture);

		//If the texture is too small, repeat in the S and T axies
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// Set the texture type if magnified or minimized
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		// load and generate the texture
		int width, height;
		unsigned char *data = SOIL_load_image(("Textures/" + id + ".png").c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		} else {
			std::cout << "[ERROR]: Could not load texture for'" << id << "'" << std::endl;
			return;
		}
		SOIL_free_image_data(data);
		atlases[id] = new Atlas(texture, rows, cols);

		std::cout << "[Console]: Loaded texture for '" << id << "'" << std::endl;

		glBindTexture(GL_TEXTURE_2D, texture);
	}

	void registerTexture(const std::string& id, const std::string& atlas, GLuint layer, GLuint x, GLuint y, GLfloat width, GLfloat height) {
		Texture* tex = new Texture(atlas, layer, x, y, width, height);
		textures[id] = tex;
		renderLayers.addElement(layer, id);
	}

	void bindTexture(const std::string& id) {
		glBindTexture(GL_TEXTURE_2D, atlases[id]->atlasID);
	}

	void unbindTexture() {
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void cleanUp() {
		for (auto iter : atlases) {
			std::cout << "[Console]: Deleting texture for '" + iter.first + "'" << std::endl;
			glDeleteTextures(1, &iter.second->atlasID);
			delete(iter.second);
		}

		for (auto iter : textures) {
			delete(iter.second);
		}
	}
}