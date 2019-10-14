#include "PostProcessing.h"
#include "src/Rendering/ModelManager.h"
#include "ContrastChanger.h"
#include "GuassianBlur.h"
#include "src/Util/Constants.h"
#include "BrightFilter.h"
#include "CombineFilter.h"

namespace PostProcessing {
	float positions[] = { -1, 1, -1, -1, 1, 1, 1, -1 };
	unsigned int vaoID;

	ContrastChanger* contrastChanger;
	GaussianBlur* hBlur;
	GaussianBlur* vBlur;

	void initialize() {
		vaoID = ModelManager::loadToVAO(positions, sizeof(positions));
		
		contrastChanger = new ContrastChanger();

		hBlur = new GaussianBlur(false, Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT);
		vBlur = new GaussianBlur(true, Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT);
	}

	void doPostProcessing(int colorTexture) {
		start();

		//hBlur->render(colorTexture);
		//vBlur->render(hBlur->getTexture());

		contrastChanger->render(colorTexture);

		stop();
	}

	void cleanUp() {
		delete contrastChanger;
		delete hBlur;
		delete vBlur;
	}

	void start() {
		glBindVertexArray(vaoID);
		glEnableVertexAttribArray(0);
	}

	void stop() {
		glDisableVertexAttribArray(0);
		glBindVertexArray(0);
	}
}