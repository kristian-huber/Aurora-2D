#pragma once
#ifndef _H_CONSTANTS
#define _H_CONSTANTS

#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec2.hpp>

namespace Constants {
	extern glm::mat4 projection;
	extern glm::mat4 textProj;

	extern int WINDOW_HEIGHT;
	extern int WINDOW_WIDTH;
	extern double mouseX;
	extern double mouseY;
	extern int seconds;
	extern int ticks;

	extern glm::vec2 camPos;
	extern float delta;

	enum RENDER_MODE {
		MAIN_MENU,
		IN_GAME
	};
};

#endif