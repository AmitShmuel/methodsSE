#include "ConsoleController.h"
#include "../Components/UIComponent.h"
#include "../Components/Button.h"
#include "../Components/TextBox.h"

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

COORD ConsoleController::getPosition() const {

		CONSOLE_SCREEN_BUFFER_INFO csbi;
		COORD coord = { -1,-1 };
		if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&csbi))
			coord.X = csbi.dwCursorPosition.X;

		if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&csbi))
			coord.Y = csbi.dwCursorPosition.Y;
		return coord;
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
void ConsoleController::listenToUserEvents() {
	INPUT_RECORD ir[5] = { 0 };
	DWORD num_read;

	while (1) {
		ReadConsoleInput(hInput, ir, 5, &num_read);
		CONSOLE_SCREEN_BUFFER_INFO cursor;
		bool tab_down = false;
		if (num_read) {
			for (int i = 0; i< (int) num_read; i++) {
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
							//printf("Mousedown");
							auto mousePos = ir[i].Event.MouseEvent.dwMousePosition;
							for (auto observer : observers) {
								if (isIntersects(mousePos, observer)) {
									//observer->click(ir[i].Event.MouseEvent)
									if (Button* btn = dynamic_cast<Button*>(observer)) {
										btn->click();
										break;
									}
									if (TextBox* textBox = dynamic_cast<TextBox*>(observer)) {
										if (mousePos.X > textBox->getXPosition() + textBox->getText().length() - 1) {
											setPosition({ textBox->getXPosition() + static_cast<short>(textBox->getText().length()) , textBox->getYPosition() });
										}
										else  setPosition(mousePos);
										break;
									}
								}
							}
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

bool ConsoleController::isIntersects(COORD mousePos, UIComponent* comp) {
	if (mousePos.X >= comp->getXPosition() && mousePos.X <= comp->getXPosition() + comp->getWidth() &&
		mousePos.Y >= comp->getYPosition() && mousePos.Y <= comp->getYPosition() + comp->getHeight()) {
		return true;
	}
	return false;
}

void ConsoleController::attachObserver(UIComponent* comp) {
	observers.push_back(comp);
}

ConsoleController::~ConsoleController() {}
