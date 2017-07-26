#pragma once
#include <Windows.h>
#include <vector>


#include <stdio.h>
#include <iostream>
#define CCTRL ConsoleController::init()
#define CCTRLDESTROY ConsoleController::destroy()

/* 
Console control wrapper class (singleton)
Use CCTRL to avoid typing ConsoleController everytime

Yftah
*/

class UIComponent;	//Handling dependency injection

class ConsoleController {
private:
	static ConsoleController *instance;	// singleton instance

	// Windows STD handlers & internal helpers
	HANDLE hOutput;						// output handler
	HANDLE hInput;						// input handler
	DWORD mode;							// current console mode
	WORD attr;							// current console text attributes
	CONSOLE_CURSOR_INFO cursorInfo;		// current console info

	// TODO: add event thread, listeners, etc	--yftah
	std::vector<UIComponent*> observers;

	// CTOR
	ConsoleController();
public:
	// singleton initializer & destroy wrapper (call destroy() at the end of the program)
	static ConsoleController& init();
	static void destroy();

	// setters
	void setPosition(COORD c);
	void setColors(short foregroundColor, bool foregroundIntensity, short backgroundColor, bool backgroundIntensity);
	void setMouseEnabled(bool isEnabled);
	void setCursorVisible(bool isVisible);
	void setCursorSize(DWORD size);

	// getters
	COORD getPosition() const;
	COORD getConsoleSize() const;
	short getTextColor() const;
	short getBackgroundColor() const;
	bool isMouseEnabled();
	bool isCursorVisible();
	DWORD getCursorSize();

	~ConsoleController();

	// Observer functions
	void listenToUserEvents();
	bool isIntersects(COORD mousePos, UIComponent* comp);
	void attachObserver(UIComponent* ob);
	void detachObserver(UIComponent* ob);
};

