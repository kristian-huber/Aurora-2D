#include "Constants.h"

namespace Constants {
	int WINDOW_HEIGHT = 1080;
	int WINDOW_WIDTH = 1980;
	double mouseX = 0;
	double mouseY = 0;
	int seconds = 0;
	int ticks = 0;

	glm::vec2 camPos = glm::vec2(0);
	float delta = 0;

	glm::mat4 projection = glm::ortho(0.0f, (float)(WINDOW_WIDTH), (float)(WINDOW_HEIGHT), 0.0f, -1.0f, 1.0f);
	glm::mat4 textProj = glm::ortho(0.0f, (float)(WINDOW_WIDTH), 0.0f, (float)(WINDOW_HEIGHT));
};