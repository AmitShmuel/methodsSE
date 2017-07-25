#include "../Components/Label.h"
#include "../Components/MessageWindow.h"
#include "../Components/NumericBox.h"
#include <iostream>
using namespace std;
/*
class ActionTest : public Action {

	virtual void action() override {
		cout << "Hello World";
	}
};
*/
void main() {


	//UIComponent *m = new MessageWindow("A Message", 0, 0, 50, 5, Solid, Orange, Blue);
	//m->draw();

	//UIComponent *l = new Label("silencio1234567",0, 0, 25, 7, Double, Blue, Green);
	//l->draw();

	/*ActionTest at;
	Button *button = new Button(&at, "Silencio1234567", 0, 0, 10, 3, Solid, Black, Green);
	button->draw();
	GFX.moveTo(0, 5);
	button->click();*/

	//delete button;
	//delete m;

	UIComponent* numBox = new NumericBox(100, 1, 100000000, 0, 0, Solid, White, Black);
	numBox->draw();
	delete numBox;
	getchar();
	CCTRLDESTROY;
}