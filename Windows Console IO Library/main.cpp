#include <iostream>
#include "Component.h"
#include "Label.h"

using namespace std;

void main() {

	Label l("SAROYA",0, 0, 10, 2, SOLID, YELLOW, BLACK);
	l.draw();
	getchar();

	//TODO: Redraw it on screen, not duplicate it!
	l.setPosition(5, 5);
	getchar();
}
