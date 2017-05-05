#pragma once
#include <Windows.h>
#define CCTRL ConsoleController::init()

/* 
Console control wrapper class (singleton)
Use CCTRL to avoid typing ConsoleController everytime

Yftah
*/
class ConsoleController {
private:
	static ConsoleController *instance;	// singleton instance

	// Windows STD handlers & internal helpers
	HANDLE hOutput;						// output handler
	HANDLE hInput;						// input handler
	DWORD mode;							// current console mode
	WORD attr;							// current console text attributes
	CONSOLE_CURSOR_INFO cursorInfo;		// current console info

	// TODO: add event listeners

	// CTOR
	ConsoleController();
public:
	// singleton initializer
	static ConsoleController& init();
	static void destroy();

	// setters
	void setPosition(COORD c);
	void setColors(short foregroundColor, bool foregroundIntensity, short backgroundColor, bool backgroundIntensity);
	void setMouseEnabled(bool isEnabled);
	void setCursorVisible(bool isVisible);
	void setCursorSize(DWORD size);

	// getters
	bool isMouseEnabled();
	bool isCursorVisible();
	DWORD getCursorSize();

	~ConsoleController();

	// test functions
	void testEvents();
	

};

