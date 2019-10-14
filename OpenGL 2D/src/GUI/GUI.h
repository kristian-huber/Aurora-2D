#pragma once
#ifndef _GUI
#define _GUI

#include "../Sprite/Sprite.h"

class GUI : public Sprite{

public:
	GUI(const std::string& texture, GLfloat x, GLfloat y) : Sprite(nullptr, texture, x, y) {}
};

#endif