#pragma once
#ifndef _H_SPRITERENDERER
#define _H_SPRITERENDERER

#include <map>
#include <vector>
#include <string>
#include "Sprite.h"
#include "SpriteShader.h"
#include "../Util/VectorMap.h"
#include "Light.h"
#include <glad/glad.h>

class SpriteRenderer {
	SpriteShader* shader;

	void prepareInstance(const Sprite* s);
	bool prepareTexture(const std::string& texture, std::string& currentAtlas);
public:
	SpriteRenderer(const glm::mat4& matrix);
	~SpriteRenderer();

	void renderSprites(const std::vector<Light>& lights, const glm::mat4& viewMatrix, VectorMap<int, Sprite*>& sprites);
};

#endif