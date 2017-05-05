#pragma once
#include <Windows.h>
class ConsoleController {
private:
	static ConsoleController *instance;
	//Windows STD handlersb & internal helpers
	HANDLE hOutput;
	HANDLE hInput;
	DWORD mode, attr;

	// CTOR
	ConsoleController();
public:
	// singleton initializer
	static ConsoleController& init();
	static void destroy();

	void setPosition(COORD c);
	void setColors(short foregroundColor, bool foregroundIntensity, short backgroundColor, bool backgroundIntensity);
	void setMouseEnabled(bool status);

	// test function
	void testEvents();
	

	~ConsoleController();
};

