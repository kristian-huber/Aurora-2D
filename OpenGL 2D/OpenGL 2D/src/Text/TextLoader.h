#pragma once
#ifndef _H_TEXT_LOADER
#define _H_TEXT_LOADER

#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <map>

namespace TextLoader {

	struct Character {
		GLuint textureID;
		glm::ivec2 size;
		glm::ivec2 bearing;
		GLuint advance;
	};

	extern std::map<GLchar, Character> characters;

	void initialize(const std::string& font);
};

#endif