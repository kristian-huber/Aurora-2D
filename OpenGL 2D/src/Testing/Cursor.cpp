#include "Cursor.h"
#include "../Util/Constants.h"

void Cursor::update(float delta) {
	x = Constants::mouseX + 22;
	y = Constants::mouseY + 26;
}