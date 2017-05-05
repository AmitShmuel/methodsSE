#include "Label.h"
#include "ConsoleController.h"
#include <iostream>
using namespace std;

void main() {
	UIComponent *l = new Label("Silencio1234567",0, 0, 50, 2, DBL, YELLOW, BLACK);
	l->draw();
	getchar();
	delete l;
	////TODO: Redraw component when using: setWidth, setHeight, setBorderType
	//l->setTextColor(GREEN);
	//l->setBackgroundColor(RED);
	//l->setBorderType(DBL);
	//getchar();

	//set cursor position example
	//INPUT_RECORD ir[5] = { 0 };
	//DWORD num_read;

	//ConsoleController c = CCTRL;
	//
	//c.setColors(WHITE, true, RED, true);
	//c.setCursorVisible(false);
	//c.setCursorVisible(true);
	//c.setMouseEnabled(true);
	//cout << c.isMouseEnabled() << endl;
	//c.setMouseEnabled(false);
	//cout << c.isMouseEnabled() << endl;
	//getchar();
//	c.setMouseEnabled(true);
	//c.testEvents();
	
	
	CCTRLDESTROY;
}
