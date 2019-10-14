#pragma once
#ifndef _H_AUDIO_MANAGER
#define _H_AUDIO_MANAGER

#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#include <string>

namespace AudioManager {
	void initalize();
	void cleanUp();

	ALuint loadWAVsound(const std::string& file);
}

#endif