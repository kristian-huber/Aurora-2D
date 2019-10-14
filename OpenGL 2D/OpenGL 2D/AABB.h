#pragma once
#ifndef H_BOUNDING_MESH
#define H_BOUNDING_MESH

#include <string>
#include <glm/vec2.hpp>

struct AABB {
	glm::vec2 axis = glm::vec2(1,0);

	float x, y, width, height;
	bool solid = true;

	AABB(float x, float y, float w, float h) : x(x), y(y), width(w), height(h) {}

	glm::vec2 getPoint(int num);
	glm::vec2 centerPoint() { return glm::vec2(x + width / 2, y + height / 2); }
	glm::vec2 topLeft() { return glm::vec2(x + width, y); }
	glm::vec2 bottomLeft() { return glm::vec2(x + width, y + height); }
	glm::vec2 bottomRight() { return glm::vec2(x, y + height); }
	glm::vec2 topRight() { return glm::vec2(x, y); }

	bool intersects(AABB* box);
};

#endif