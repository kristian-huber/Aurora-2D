#include "AudioManager2.h"
#include <iostream>
#include <fstream>
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#include <map>

namespace AudioManager2{
	std::map<std::string, ALuint> bufferIDs;

	ALCdevice* device;
	ALCcontext* context;
	ALuint source;

	void initialize() {
		
		device = alcOpenDevice(NULL);
		if (!device) {
			ALCenum error = alGetError();
			std::cout << "[ERROR]: Initializing OpenAL device - " << error << std::endl;
		}

		context = alcCreateContext(device, NULL);
		if (!alcMakeContextCurrent(context)) {
			ALCenum error = alGetError();
			std::cout << "[ERROR]: Creating current context for OpenAL - " << error << std::endl;
		}

		//Indicate which direction is forward and up
		ALfloat listenerOri[] = { 0, 0, 1, 0, 1, 0 };

		//Initialize the listener
		alListener3f(AL_POSITION, 0, 0, 1);
		alListener3f(AL_VELOCITY, 0, 0, 0);
		alListenerfv(AL_ORIENTATION, listenerOri);

		//Generate a source
		alGenSources((ALuint)1, &source);

		alSourcef(source, AL_PITCH, 1);
		alSourcef(source, AL_GAIN, 1);
		alSource3f(source, AL_POSITION, 0, 0, 0);
		alSource3f(source, AL_VELOCITY, 0, 0, 0);
		alSourcei(source, AL_LOOPING, AL_FALSE);
	}

	void playSound(const std::string& id) {

		//Check for errors here if the id doesn't exist
		//Put the CD in the cd player
		alSourcei(source, AL_BUFFER, bufferIDs[id]);

		alSourcePlay(source);
	}

	void cleanUp() {
		alDeleteSources(1, &source);
		
		for (auto iter = bufferIDs.begin(); iter != bufferIDs.end(); iter++) {
			alDeleteBuffers(1, &iter->second);
		}

		device = alcGetContextsDevice(context);
		alcMakeContextCurrent(NULL);
		alcDestroyContext(context);
		alcCloseDevice(device);
	}

	bool isBigEndian(){
		int a = 1;
		return !((char*)&a)[0];
	}

	int convertToInt(char* buffer, int len) {
		int a = 0;
		if (!isBigEndian()){
			for (int i = 0; i < len; i++) {
				((char*)&a)[i] = buffer[i];
			}
		} else {
			for (int i = 0; i < len; i++) {
				((char*)&a)[3 - i] = buffer[i];
			}
		}
		return a;
	}

	char* loadWAVData(const std::string& file, int& channels, int& samplerate, int& bps, int& size){
		
		/* http://soundfile.sapp.org/doc/WaveFormat/ */

		char buffer[4];
		std::ifstream in(file, std::ios::binary);
		
		//Chunk ID (Says "RIFF")
		in.read(buffer, 4);
		if (strncmp(buffer, "RIFF", 4) != 0){
			std::cout << "[ERROR]: Invalid WAV file '" << file << "'" << std::endl;
			return nullptr;
		}
		
		in.read(buffer, 4); //Chunk size
		in.read(buffer, 4);	//Format (Says "WAVE")
		in.read(buffer, 4);	//Subchunk1ID (Says "fmt ")
		in.read(buffer, 4);	//16 for PCM
		in.read(buffer, 2);	//Audio Format
		in.read(buffer, 2); // NumChannels
		channels = convertToInt(buffer, 2);
		
		in.read(buffer, 4); // Sample Rate
		samplerate = convertToInt(buffer, 4);
		
		in.read(buffer, 4);	//ByteRate
		in.read(buffer, 2); //Block Align
		in.read(buffer, 2); //Bits per sample
		bps = convertToInt(buffer, 2);

		in.read(buffer, 4); // This will either say "data" or have extra parameters
		if (strncmp(buffer, "data", 4) == 0){

			in.read(buffer, 4); // NumSamples * Num Channels * BitsPerSample/8
								// This is the number of btyes in the data (size of the subchunk following this number)
			size = convertToInt(buffer, 4);
			
			char* data = new char[size];
			in.read(data, size);
			std::cout << "[Console]: Loaded WAV data";
			return data;

		// Has extra parameters
		}else{
			char pastLetters[4];

			for (int i = 0; i < 100; i++) {
				char letter;
				in.read(&letter, 1);
				
				pastLetters[0] = pastLetters[1];
				pastLetters[1] = pastLetters[2];
				pastLetters[2] = pastLetters[3];
				pastLetters[3] = letter;

				if (pastLetters[0] == 'd' && pastLetters[1] == 'a' && pastLetters[2] == 't' && pastLetters[3] == 'a') {
					std::cout << "[WARNING]: Had to search for data in '" << file << "'" << std::endl;

					in.read(buffer, 4);	//The size in bytes of data
					size = convertToInt(buffer, 4);

					std::cout << "[Console] The size of this WAV is " << size << " for '" << file << "'" << std::endl;

					char* data = new char[size];
					in.read(data, size);

					return data;
				}
			}

			std::cout << "[ERROR]: WAV file does not have data '" << file << "'" << std::endl;
			return nullptr;
		}
	}

	void loadWAV(const std::string& id){

		ALuint bufferID;
		alGenBuffers(1, &bufferID);

		int channel, sampleRate, bps, size;
		char* WAVData = loadWAVData(("Sounds/" + id + ".wav"), channel, sampleRate, bps, size);

		ALuint format;
		if (channel == 1){
			format = (bps == 8) ? AL_FORMAT_MONO8 : AL_FORMAT_MONO16;
		} else {
			format = (bps == 8) ? AL_FORMAT_STEREO8 : AL_FORMAT_STEREO16;
		}

		alBufferData(bufferID, format, WAVData, size, sampleRate);

		if (WAVData) {
			free(WAVData);
			bufferIDs[id] = bufferID;
		}else {
			std::cout << "[ERROR]: Could not load WAV file '" << id << "'" << std::endl;
		}
	}
}