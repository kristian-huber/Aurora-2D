#pragma once
#ifndef _H_TEXT
#define _H_TEXT

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <string>

struct Text {
	glm::vec3 color = glm::vec3(1, 1, 1);
	glm::vec2 position = glm::vec2(0, 0);
	float scale = 3;
	std::string text = "";

	Text(const std::string& text) : text(text) {}

	void update() {}
};

#endif