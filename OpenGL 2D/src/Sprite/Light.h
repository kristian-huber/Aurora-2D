#pragma once
#ifndef _H_LIGHT
#define _H_LIGHT

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

struct Light {
	glm::vec2 position;
	glm::vec4 color;
	float radius;

	Light(float x, float y, float r, float g, float b, float rad) : position(glm::vec2(x, y)), color(glm::vec4(r, g, b, 0.1f)), radius(rad) {}
	Light(glm::vec2 pos, float r, float g, float b, float rad) : position(pos), color(glm::vec4(r, g, b, 0.1f)), radius(rad) {}
	Light(glm::vec2 pos) : position(pos), color(1, 1, 1, 0.1f), radius(100) {}
};

#endif