#include "Label.h"

using namespace std;

void main() {

	Label l("SAROYA",0, 0, 10, 2, DOTTED, YELLOW, BLACK);
	l.draw();
	getchar();

	//TODO: Redraw component when using: setWidth, setHeight, setBorderType
	l.setTextColor(GREEN);
	getchar();
}
