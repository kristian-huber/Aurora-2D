#pragma once
#ifndef _H_SPRITE
#define _H_SPRITE

#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <string>
#include <vector>
#include "../../AABB.h"

class World;
class BoundingMesh;

class Sprite {
protected:
	std::vector<std::string> textures = std::vector<std::string>();
public:
	GLfloat xVelocity, yVelocity;
	GLfloat width, height;
	GLfloat x, y;
	AABB* boundingBox;
	World* world;

	//Don't forget to update this if the object is moving
	BoundingMesh* bounds = nullptr;

	// Makes checking collision detection faster. Really only applies to entities with bounding boxes anyway
	bool moving = false;

	Sprite(World* world, const std::string& texture, GLfloat x, GLfloat y) : Sprite(world, x, y, 1, texture) {}
	Sprite(World* world, GLfloat x, GLfloat y, int noTex, const std::string& textures...);
	~Sprite();

	virtual std::string& getTexture();
	virtual void update(float delta);

	//You need to call this if your object is solid
	virtual void onCollision(Sprite* obj);
};

#endif