#pragma once
#ifndef _H_PLAYER
#define _H_PLAYER

#include "../Sprite/Sprite.h"

class World;

class Player : public Sprite {
	char direction = 'd';
	int speed = 200;

public:
	Player(World* world, float x, float y);

	void setDirection(char c);
	std::string& getTexture() override;
	void update(float delta) override;
};

#endif