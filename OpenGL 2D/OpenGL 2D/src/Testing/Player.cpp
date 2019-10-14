#include "Player.h"
#include "../Util/InputManager.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "../Testing/World.h"

Player::Player(World* world, float x, float y) : Sprite(world, x, y, 4, "Character_Front", "Character_Back", "Character_Left", "Character_Right") {
	boundingBox = new AABB(x, y, 64, 128);
	boundingBox->solid = false;
}

void Player::setDirection(char c) {
	direction = c;
}

std::string& Player::getTexture(){
	switch (direction) {
	case 'd':
		return textures[0];
		break;
	case 'u':
		return textures[1];
		break;
	case 'l':
		return textures[2];
		break;
	case 'r':
		return textures[3];
		break;
	default:
		return textures[0];
	}
}

void Player::update(float delta) {
	
	Sprite::update(delta);

	//Y
	if (InputManager::KEYS[GLFW_KEY_W]) {
		yVelocity = -speed;
		setDirection('u');
	}else if (InputManager::KEYS[GLFW_KEY_S]) {
		yVelocity = speed;
		setDirection('d');
	}

	if (!InputManager::KEYS[GLFW_KEY_S] && !InputManager::KEYS[GLFW_KEY_W]) {
		yVelocity = 0;
	}

	//X
	if (InputManager::KEYS[GLFW_KEY_A]) {
		xVelocity = -speed;
		setDirection('l');
	}else if (InputManager::KEYS[GLFW_KEY_D]) {
		xVelocity = speed;
		setDirection('r');
	}

	if (!InputManager::KEYS[GLFW_KEY_A] && !InputManager::KEYS[GLFW_KEY_D]) {
		xVelocity = 0;
	}
}