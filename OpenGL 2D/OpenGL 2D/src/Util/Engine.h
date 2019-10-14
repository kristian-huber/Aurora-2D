#pragma once
#ifndef _H_ENGINE
#define _H_ENGINE

#include <string>

class MasterRenderer;

class Engine {
protected:
	MasterRenderer* renderer;
	float delta = 0;

	virtual void initialize() {}
	virtual void loadResources() {}
	virtual void loop() {};
public:
	~Engine();
	void start(const std::string& windowName);
};

#endif