#include "AudioManager.h"
#include <iostream>
#include <fstream>
#include <cstring>

namespace AudioManager {
	ALCdevice* device;
	ALuint source;
	ALuint buffer;
	ALCcontext* context;

	void initalize() {
		
		//Initalize the audio
		device = alcOpenDevice(NULL);
		if (!device) {
			std::cout << "[ERROR]: Could not find an audio device" << std::endl;
		}

		context = alcCreateContext(device, NULL);
		if (!alcMakeContextCurrent(context)) {
			ALCenum error = alGetError();
			if (error != AL_NO_ERROR)
				std::cout << "[ERROR]: Could not make the device current context" << std::endl;
		}

		//Set up the listener

		// The first 3 numbers indicate an 'at' vector. Its a vector pointing +z
		// The second 3 numbers indicate an 'up' vector. Its a vector pointing +y
		ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };

		alListener3f(AL_POSITION, 0, 0, 0.1f);
		alListener3f(AL_VELOCITY, 0, 0, 0);
		alListenerfv(AL_ORIENTATION, listenerOri);

		// Set up the source of the audio
		alGenSources((ALuint)1, &source);

		alSourcef(source, AL_PITCH, 1);
		alSourcef(source, AL_GAIN, 1);
		alSource3f(source, AL_POSITION, 0, 0, 0);
		alSource3f(source, AL_VELOCITY, 0, 0, 0);
		alSourcei(source, AL_LOOPING, AL_TRUE);

		// Load a wav file
		buffer = loadWAVsound("UpInTheSky");
		alSourcei(source, AL_BUFFER, buffer);
		alSourcePlay(source);
	}

	void cleanUp() {
		alDeleteSources(1, &source);
		alDeleteBuffers(1, &buffer);
		device = alcGetContextsDevice(context);
		alcMakeContextCurrent(NULL);
		alcDestroyContext(context);
		alcCloseDevice(device);
	}

	bool isBigEndian(){
		int a = 1;
		return !((char*)&a)[0];
	}

	int convertToInt(char* buffer, int len){
		int a = 0;
		if (!isBigEndian())
			for (int i = 0; i < len; i++)
				((char*)&a)[i] = buffer[i];
		else
			for (int i = 0; i < len; i++)
				((char*)&a)[3 - i] = buffer[i];
		return a;
	}

	char* loadWAV(const char* fn, int& chan, int& samplerate, int& bps, int& size){
		char buffer[4];
		std::ifstream in(fn, std::ios::binary);
		in.read(buffer, 4);

		if (strncmp(buffer, "RIFF", 4) != 0){
			std::cout << "[ERROR]: Invalid WAV file" << std::endl;
			return NULL;
		}

		in.read(buffer, 4);
		in.read(buffer, 4);      //WAVE
		in.read(buffer, 4);      //fmt
		in.read(buffer, 4);      //16
		in.read(buffer, 2);      //1
		in.read(buffer, 2);
		chan = convertToInt(buffer, 2);
		
		in.read(buffer, 4);
		samplerate = convertToInt(buffer, 4);
		
		in.read(buffer, 4);
		in.read(buffer, 2);
		in.read(buffer, 2);
		bps = convertToInt(buffer, 2);
		
		in.read(buffer, 4);      //data
		in.read(buffer, 4);
		size = convertToInt(buffer, 4);
		
		char* data = new char[size];
		in.read(data, size);
		return data;
	}

	ALuint loadWAVsound(const std::string& sound) {
		int channel, sampleRate, bps, size;
		char* data = loadWAV(("/Sounds/" + sound + ".wav").c_str(), channel, sampleRate, bps, size);

		ALuint bufferID, format;
		alGenBuffers(1, &bufferID);
		if (channel == 1){
			format = (bps == 8) ? AL_FORMAT_MONO8 : AL_FORMAT_MONO16;
		}else {
			format = (bps == 8) ? AL_FORMAT_STEREO8 : AL_FORMAT_STEREO16;
		}
		alBufferData(bufferID, format, data, size, sampleRate);

		return bufferID;
	}
}