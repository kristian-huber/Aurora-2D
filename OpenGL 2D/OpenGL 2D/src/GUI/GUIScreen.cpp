#include "GUIScreen.h"

void GUIScreen::update(float delta) {
	for (auto iter = guis.begin(); iter != guis.end(); iter++) {
		for (GUI* gui : iter->second) {
			gui->update(delta);
		}
	}
	for (Text& text : texts) {
		text.update();
	}
}