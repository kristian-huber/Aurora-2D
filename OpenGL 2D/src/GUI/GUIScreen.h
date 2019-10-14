#pragma once
#ifndef _H_GUI_SCREEN
#define _H_GUI_SCREEN

#include "../Util/VectorMap.h"
#include "GUI.h"
#include "../Text/Text.h"
#include <vector>

struct GUIScreen{
	VectorMap<int, GUI*> guis = VectorMap<int, GUI*>();
	std::vector<Text> texts = std::vector<Text>();

	void update(float delta);
};

#endif

