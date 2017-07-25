#include "Label.h"
#include "ConsoleController.h"
#include "../Common/Graphics.h"
#include <iostream>
using namespace std;

void main() {
	//Graphics g = Graphics();
	GFX.setBackground(Blue);
	GFX.clearScreen();
	UIComponent *l = new Label("Silencio1234567",0, 0, 50, 2, Double, BrightOrange, Blue);
	l->draw();

	delete l;
	getchar();
	GFX_DESTROY;

}
