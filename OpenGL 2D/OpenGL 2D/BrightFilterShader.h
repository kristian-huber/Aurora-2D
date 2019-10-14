#pragma once
#ifndef _H_BRIGHT_FILTER_SHADER
#define _H_BRIGHT_FILTER_SHADER

#include "src/Rendering/BaseShader.h"

class BrightFilterShader : public BaseShader{
public:
	BrightFilterShader() : BaseShader("FBOVertShader.txt", "FBOBrightFilterFrag.txt") {}
};

#endif