#include "Test.h"
#include "../Util/Constants.h"

//MOVE STUFF FROM CONSTANTS TO INPUT MANAGER. ALSO MAKE IT A NAMESPACE
//Make a class that sprite and GUI inherit from
//Text does not stay on top based on window size

int main() {
	//Constants::WINDOW_WIDTH = 800;
	//Constants::WINDOW_HEIGHT = 500;

	Test t = Test();
	t.start("OpenGL Testing");

	return 0;
}