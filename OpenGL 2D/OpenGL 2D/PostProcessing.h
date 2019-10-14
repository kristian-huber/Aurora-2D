#pragma once
#ifndef _H_POSTPROCESSING
#define _H_POSTPROCESSING

namespace PostProcessing {
	void initialize();
	void doPostProcessing(int colorTexture);
	void cleanUp();
	void start();
	void stop();
};

#endif