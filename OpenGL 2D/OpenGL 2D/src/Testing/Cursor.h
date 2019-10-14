#pragma once
#ifndef _H_CURSOR
#define _H_CURSOR

#include "../GUI/GUI.h"

struct Cursor : public GUI {
	Cursor(const std::string& id) : GUI(id, 0, 0) {}
	void update(float delta) override;
};

#endif