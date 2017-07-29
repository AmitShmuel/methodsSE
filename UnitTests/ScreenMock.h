#pragma once
#include "../Common/ConsoleController.h"

#define SCREEN ScreenMock::init()

class ScreenMock {

	static ScreenMock *instance;
	std::stringstream *screen;

	ScreenMock();

public:

	static ScreenMock& init();
	static void destroy();

	void setY(int index) { 
		std::cout.rdbuf(screen[index].rdbuf()); 
	}

	void setX(int index) { 
		for (int i = 0; i < index; ++i) std::cout << " ";
	}

	std::stringstream* getScreen() const { return screen; }
};