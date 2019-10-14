#pragma once
#ifndef _H_TEST
#define _H_TEST

#include "../Util/Engine.h"

class World;
class GUIScreen;

class Test : public Engine {
	World* w;
	GUIScreen* inGame;

	void initialize() override;
	void loop() override;
	void loadResources() override;
};

#endif