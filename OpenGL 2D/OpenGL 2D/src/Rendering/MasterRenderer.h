#pragma once
#ifndef _H_MASTERRENDERER
#define _H_MASTERRENDERER

#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>
#include <map>
#include "../Sprite/SpriteRenderer.h"
#include "../Testing/World.h"
#include "../GUI/GUIRenderer.h"
#include "../GUI/GUIScreen.h"
#include "../Text/TextRenderer.h"
#include "../Util/Constants.h"
#include "../FBO/FBO.h"

using namespace Constants;

class MasterRenderer {	
	glm::mat4 viewMatrix = glm::mat4(1.0);
	glm::vec2 cameraPos = glm::vec2(0.0f,0.0f);

	SpriteRenderer* spriteRenderer;
	GUIRenderer* guiRenderer;
	TextRenderer* textRenderer;

	FBO* fbo;

	void update(GLfloat delta);
public:
	MasterRenderer();
	~MasterRenderer();
	void render(GLfloat delta, World& world, GUIScreen& screen);
};

#endif