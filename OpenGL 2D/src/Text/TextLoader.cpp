#include "TextLoader.h"
#include <iostream>
#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace TextLoader {

	std::map<GLchar, Character> characters = std::map<GLchar, Character>();

	void initialize(const std::string& font) {

		// Initialize library
		FT_Library ft;
		if (FT_Init_FreeType(&ft))
			std::cout << "[ERROR]: Could not initialize FreeType Library" << std::endl;
		
		FT_Face face;
		if (FT_New_Face(ft, ("fonts/" + font + ".ttf").c_str(), 0, &face))
			std::cout << "[ERROR]: Failed to load font" << std::endl;

		// Tell it what font size to extract
		FT_Set_Pixel_Sizes(face, 0, 16);
	
		//Clear characters
		characters.clear();

		for (GLubyte c = 0; c < 128; c++) {

			// Set the active glyph
			// We created an 8-bit grayscale bitmap image at face->glyph->bitmap
			if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
				std::cout << "[ERROR]: Failed to load glyph '" << (char)c << "'";
				continue;
			}

			// Disable byte-alignment resistriction?
		// This makes it so we don't have to use a multiple of 4
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			//Generate Texture
			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
						GL_TEXTURE_2D,
						0, 
						GL_RED,
						face->glyph->bitmap.width,
						face->glyph->bitmap.rows,
						0,
						GL_RED,
						GL_UNSIGNED_BYTE,
						face->glyph->bitmap.buffer
			);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			//Now store the characters
			Character character{
				texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				face->glyph->advance.x
			};
			characters[c] = character;
		}

		glBindTexture(GL_TEXTURE_2D, 0);

		FT_Done_Face(face);
		FT_Done_FreeType(ft);
	}
}