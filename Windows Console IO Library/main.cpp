#include "Label.h"
#include "ConsoleController.h"
#include <iostream>
using namespace std;

void main() {
	//UIComponent *l = new Label("Silencio1234567",0, 0, 50, 2, DOTTED, YELLOW, BLACK);
	//l->draw();
	//getchar();

	////TODO: Redraw component when using: setWidth, setHeight, setBorderType
	//l->setTextColor(GREEN);
	//l->setBackgroundColor(RED);
	//l->setBorderType(DBL);
	//getchar();

	//set cursor position example
	INPUT_RECORD ir[5] = { 0 };
	DWORD num_read;

	ConsoleController c = ConsoleController::init();
	c.setColors(WHITE, true, RED, true);
	cout << "Hello";
	getchar();
//	c.setMouseEnabled(true);
	//c.testEvents();
	
	
	ConsoleController::destroy();
}
