#pragma once
#ifndef _H_AUDIO_MANAGER2
#define _H_AUDIO_MANAGER2

#include <string>

namespace AudioManager2{

	void initialize();

	void playSound(const std::string& id);

	void cleanUp();

	char* loadWAVData(const std::string& file, int& channels, int& samplerate, int& bps, int& size);

	void loadWAV(const std::string& id);
}

#endif