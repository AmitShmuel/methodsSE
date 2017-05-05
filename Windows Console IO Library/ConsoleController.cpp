#include "ConsoleController.h"
#include <stdio.h>
#include <iostream>
// init static
ConsoleController *ConsoleController::instance = 0;

// private CTOR for jesus
ConsoleController::ConsoleController() : hOutput(GetStdHandle(STD_OUTPUT_HANDLE)), hInput(GetStdHandle(STD_INPUT_HANDLE)) {
	GetConsoleMode(hInput, &mode);
	GetConsoleCursorInfo(hOutput, &cursorInfo);
}

// Init console controller
ConsoleController& ConsoleController::init() {
	if (instance == 0) {
		instance = new ConsoleController();
	}
	return *instance;
}

// destroy the controller
void ConsoleController::destroy() {
	if (instance != 0) delete instance;
}

// sets current cursor position
void ConsoleController::setPosition(COORD c) {
	SetConsoleCursorPosition(hOutput, c);
}

// sets text console attribute
void ConsoleController::setColors(short foregroundColor, bool foregroundIntensity, short backgroundColor, bool backgroundIntensity) {
	attr = foregroundColor | FOREGROUND_INTENSITY * foregroundIntensity | 16 * backgroundColor | BACKGROUND_INTENSITY * backgroundIntensity;
	SetConsoleTextAttribute(hOutput, attr);
}

void ConsoleController::setMouseEnabled(bool isVisibile) {
	// TODO: FIXME: this does not seem to have any effect
	//std::cout << (mode | ENABLE_MOUSE_INPUT) << std::endl;
	mode = (isVisibile) ? mode | ENABLE_MOUSE_INPUT : mode & ~ENABLE_MOUSE_INPUT;
	//std::cout << mode << std::endl;
	SetConsoleMode(hInput, ENABLE_MOUSE_INPUT);
}

void ConsoleController::setCursorVisible(bool isVisible) {
	cursorInfo.bVisible = isVisible;
	SetConsoleCursorInfo(hOutput, &cursorInfo);
}

void ConsoleController::setCursorSize(DWORD size) {
	cursorInfo.dwSize = size;
	SetConsoleCursorInfo(hOutput, &cursorInfo);
}

bool ConsoleController::isMouseEnabled() {
	return (mode & ENABLE_MOUSE_INPUT) > 0;
}

bool ConsoleController::isCursorVisible() {
	return cursorInfo.bVisible;
}

DWORD ConsoleController::getCursorSize() {
	return cursorInfo.dwSize;
}

// test code for events 
// TODO: event thread and attach listeners
void ConsoleController::testEvents() {
	INPUT_RECORD ir[5] = { 0 };
	DWORD num_read;

	while (1) {
		ReadConsoleInput(hInput, ir, 5, &num_read);
		CONSOLE_SCREEN_BUFFER_INFO cursor;
		bool tab_down = false;
		if (num_read) {
			for (int i = 0; i<num_read; i++) {
				switch (ir[i].EventType) {
				case KEY_EVENT:
					KEY_EVENT_RECORD key = ir[i].Event.KeyEvent;
					if (key.bKeyDown) {
						switch (key.wVirtualKeyCode) {
						case VK_TAB:

							goto end;
							break;
						default:
							SetConsoleCursorPosition(hOutput, { 0,0 });
							printf("x");
							break;
						}
						setMouseEnabled(false);
					}
					/*printf("key %s it's virtual key code value %d\n",
					ir[i].Event.KeyEvent.bKeyDown ? "down" : "up",
					ir[i].Event.KeyEvent.wVirtualKeyCode);*/
					break;
				case MOUSE_EVENT:
					switch (ir[i].Event.MouseEvent.dwButtonState) {
					case RI_MOUSE_LEFT_BUTTON_DOWN:

							SetConsoleCursorPosition(hOutput, { 0,0 });
							printf("Mousedown");
						
						break;
					case RI_MOUSE_LEFT_BUTTON_UP:
						SetConsoleCursorPosition(hOutput, { 0,0 });
						printf("         ");
						/*SetConsoleCursorPosition(h, { 0,0 });
						printf("\b                   \b");
						printf("Mouseup");*/
						break;
					}
					break;
				}
			}
		}
	}
end:
	return;
}


ConsoleController::~ConsoleController() {}
