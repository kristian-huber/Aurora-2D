#include "World.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <GLFW/glfw3.h>
#include "../Util/Constants.h"
#include "../Rendering/TextureManager.h"
#include "../Util/InputManager.h"
#include "../../AABB.h"
#include "Player.h"
#include "../Sprite/Sprite.h"

World::World() {
	sprites.keepList = true;

	player = new Player(this, 16 * 64, 8 * 64);
	addSprite(player);

	generateWorld();
}

World::~World() {
	std::cout << "[Console]: Deleting Sprites" << std::endl;

	for (auto iter = sprites.begin(); iter != sprites.end(); iter++) {
		for (Sprite* s : iter->second) {
			delete s;
		}
	}
}

bool World::intersectsAnything(Sprite* sprite) {
	if (sprite->boundingBox == nullptr) return false;

	for (Sprite* s : sprites.getList()) {
		if (s->boundingBox != nullptr && sprite != s && sprite->boundingBox->intersects(s->boundingBox)) {
			return true;
		}
	}

	return false;
}

void World::generateWorld() {
	int size = 64;

	addSprite(new Sprite(this, "House", 8 * size, 4 * size));

	addSprite(new Sprite(this, "Bush_L", 14 * size, 6 * size));
	addSprite(new Sprite(this, "Bush_C", 15 * size, 6 * size));
	addSprite(new Sprite(this, "Bush_R", 16 * size, 6 * size));

	addSprite(new Sprite(this, "Bush_L", 18 * size, 6 * size));
	addSprite(new Sprite(this, "Bush_C", 19 * size, 6 * size));
	addSprite(new Sprite(this, "Bush_R", 20 * size, 6 * size));

	addSprite(new Sprite(this, "Cave", 17 * size, 5 * size));

	Sprite* tree1 = new Sprite(this, "Tree", 10 * size, 12 * size);
	tree1->boundingBox = new AABB(10 * size, 12 * size, 128, 128);
	addSprite(tree1);

	Sprite* tree2 = new Sprite(this, "Tree", 19 * size, 14 * size);
	addSprite(tree2);

	for (int i = 0; i < 36; i++) {
		for (int j = -2; j < 2; j++) {
			addSprite(new Sprite(this, i * size, j * size, 4, "Water1", "Water2", "Water3", "Water4"));
		}
	}

	for (int i = 0; i < 36; i++) {
		addSprite(new Sprite(this, "Cliff_TopC", i * size, 2 * size));
		addSprite(new Sprite(this, "Cliff_UpMid", i * size, 3 * size));
		addSprite(new Sprite(this, "Cliff_LowMid", i * size, 4 * size));

		if (i != 17) {
			addSprite(new Sprite(this, "Cliff_BottomC", i * size, 5 * size));
		}else{
			addSprite(new Sprite(this, "entrance", i * size, 5 * size));
		}
	}
	
	for (int i = 0; i < 36; i++) {
		for (int j = 6; j < 24; j++) {
			addSprite(new Sprite(this, "Grass", i * size, j * size));
		}
	}
}

void World::update(float delta) {
	for (Sprite* sprite : sprites.getList()) {
			
		//Check for collision detection THIS NEEDS TO BE BETTER THAN N^2
		if (sprite->boundingBox != nullptr) {
			for (Sprite* obj : sprites.getList()) {

				if (obj != sprite && obj->boundingBox != nullptr && obj->boundingBox->intersects(sprite->boundingBox)) {
					obj->onCollision(sprite);
					sprite->onCollision(obj);
				}
			}
		}

		//Update the sprites
		sprite->update(delta);
	}
}

void World::addSprite(Sprite* sprite) {
	int layer = TextureManager::textures[sprite->getTexture()]->layer;
	sprites.addElement(layer, sprite);
}

void World::deleteSprite(Sprite* sprite) {
	int layer = TextureManager::textures[sprite->getTexture()]->layer;
	sprites.removeElement(layer, sprite);
	delete(sprite);
}