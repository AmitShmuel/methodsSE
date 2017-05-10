#include "Button.h"
#include "ConsoleController.h"
#include "NumericBox.h"
using namespace std;

//int myFunction1(int x, double y) {return x * y;}

void main() {

	auto numericBox = new NumericBox(5, 0, 200, 0, 0, 10, 2, DOTTED, YELLOW, BLACK);
	numericBox->draw();
	getchar();
	try {
		numericBox->decrement();
		numericBox->decrement();
		numericBox->decrement();
		numericBox->decrement();
		numericBox->decrement();
		numericBox->decrement();
	}
	catch(IOConsoleException& e) {
		cout <<"\n\n" <<e.what();
	}

	getchar();

	delete numericBox;

	//Label *l = new Label("Silencio1234567",0, 0, 10, 2, DOTTED, YELLOW, LIGHTBLUE);
	//l->draw();
	//getchar();
	//l->setBorderType(SOLID);
	//getchar();
	//delete l;

	//	   Ret, param, param   func pointer  text on button    x  y  w   h  border color txt  color bg
	//Button<int, int, double> b(&myFunction1,"Silencio1234567", 0, 0, 10, 2, DOTTED, YELLOW, LIGHTBLUE);
	//b.draw();
	//auto b = new Button<int, int, double>(&myFunction1, "Silencio1234567", 0, 0, 10, 2, DOTTED, YELLOW, LIGHTBLUE);
	//int x = 10;
	//double y = 20;
	//int z = b(x, y);
	//int z = (*b)(x,y);
	//cout << "\n\n" << z;
	//delete b;
	//getchar();
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
