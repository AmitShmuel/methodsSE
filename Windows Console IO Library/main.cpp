#include "../Components/Label.h"
#include "../Components/MessageWindow.h"
//#include "ConsoleController.h"
#include "../Common/Graphics.h"
#include "../Components/Button.h"
#include "../Common/Action.h"
#include "../Common/IOConsoleException.h"
#include <iostream>
using namespace std;

class ActionTest : public Action {

	virtual void action() override {
		cout << "Hello World";
	}
};

void main() {

	//Graphics g = Graphics();
	try {
		GFX.setBackground(Blue);
		GFX.clearScreen();
	}
	catch (const IOConsoleException&) {
		cout << "Just an example..\n";
	}

	UIComponent *m = new MessageWindow("A Message", 0, 0, 50, 5, Solid, Orange, Blue);
	m->draw();

	//UIComponent *l = new Label("Silencio1234567",0, 0, 50, 4, Double, BrightOrange, Blue);
	//l->draw();

	/*ActionTest at;
	Button *button = new Button(&at, "Silencio1234567", 0, 0, 10, 3, Solid, Black, Green);
	button->draw();
	GFX.moveTo(0, 5);
	button->click();*/
	
	//delete button;
	//delete l;
	delete m;

	getchar();
	GFX.moveTo(0, 10);
	GFX_DESTROY;
}
