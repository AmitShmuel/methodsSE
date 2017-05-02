#include "Label.h"
using namespace std;

void main() {
	UIComponent *l = new Label("Silencio1234567",0, 0, 50, 2, DOTTED, YELLOW, BLACK);
	l->draw();
	getchar();

	//TODO: Redraw component when using: setWidth, setHeight, setBorderType
	l->setTextColor(GREEN);
	l->setBackgroundColor(RED);
	l->setBorderType(DBL);
	getchar();
	delete l;
}
