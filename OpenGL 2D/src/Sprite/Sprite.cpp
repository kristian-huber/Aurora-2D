#include "Sprite.h"
#include "../Rendering/TextureManager.h"
#include "../Util/Constants.h"
#include <iostream>
#include <math.h>
#include <string>
#include "../Testing/World.h"

Sprite::Sprite(World* world, GLfloat x, GLfloat y, int noTex, const std::string& textures...) : x(x), y(y), xVelocity(0), yVelocity(0) {
	
	this->world = world;
	
	va_list varList;

	va_start(varList, noTex);

	for (int i = 0; i < noTex; i++){

		const char* temp = va_arg(varList, const char*);
		std::string tex(temp);

		if (i == 0) {
			width = TextureManager::textures[tex]->width * TextureManager::STANDARD_TILE_SIZE;
			height = TextureManager::textures[tex]->height * TextureManager::STANDARD_TILE_SIZE;
		}

		this->textures.push_back(tex);
	}

	va_end(varList);
}

Sprite::~Sprite() {
	if (bounds != nullptr) {
		delete bounds;
	}
}

std::string& Sprite::getTexture() {
	int index = Constants::seconds % textures.size();
	return textures[index];
}

void Sprite::update(float delta) {

	float dx = xVelocity * delta;
	float dy = yVelocity * delta;

	if (boundingBox != nullptr) {
		x += dx;
		y += dy;
		boundingBox->x += dx;
		boundingBox->y += dy;

		if (world->intersectsAnything(this)) {
			std::cout << "Collision" << std::endl;

			dx *= -1.01;
			dy *= -1.01;
		} else {
			dx = 0;
			dy = 0;
		}
	}

	x += dx;
	y += dy;
	if (boundingBox != nullptr) {
		boundingBox->x += dx;
		boundingBox->y += dy;
	}
}

void Sprite::onCollision(Sprite* obj) {
	
}