#pragma once
#ifndef _GUI_RENDERER
#define _GUI_RENDERER

#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include "GUI.h"
#include "GUIShader.h"
#include "../Util/VectorMap.h"

class GUIRenderer {
	GUIShader* shader;

	void prepareInstance(const GUI* gui);
	bool prepareTexture(const std::string& texture, std::string& currentAtlas);
public:
	GUIRenderer(const glm::mat4& matrix);
	~GUIRenderer();

	void renderGUIs(VectorMap<int, GUI*>& guis);
};

#endif