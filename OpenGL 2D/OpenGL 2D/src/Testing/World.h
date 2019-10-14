#pragma once
#ifndef _H_WORLD
#define _H_WORLD

#include <string>
#include <vector>
#include "../Util/VectorMap.h"
#include "../Sprite/Light.h"

class Sprite;

class Player;

class World {
	VectorMap<int, Sprite*> sprites = VectorMap<int, Sprite*>();
	Player* player;

	void generateWorld();
public:
	std::vector<Light> lights = std::vector<Light>();

	World();
	~World();

	void addSprite(Sprite* s);
	void deleteSprite(Sprite* s);
	void update(float delta);

	bool intersectsAnything(Sprite* s);
	
	VectorMap<int, Sprite*>& getSprites() { return sprites; }
};

#endif