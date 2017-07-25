#include "../Components/Label.h"
#include "../Components/MessageWindow.h"
//#include "ConsoleController.h"
#include "../Common/Graphics.h"
#include <iostream>
using namespace std;

void main() {
	//Graphics g = Graphics();
	GFX.setBackground(Blue);
	GFX.clearScreen();
	//UIComponent *l = new Label("Silencio1234567",0, 0, 50, 4, Double, BrightOrange, Blue);
	//l->draw();

	UIComponent *m = new MessageWindow("A Message Window", 0, 0, 50, 4, Solid, Orange, Blue);
	m->draw();

	//delete l;
	delete m;
	getchar();
	GFX_DESTROY;
}
