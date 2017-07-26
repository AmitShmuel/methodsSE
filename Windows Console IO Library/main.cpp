#include "../Components/Label.h"
#include "../Components/MessageWindow.h"
#include "../Components/NumericBox.h"
#include "../Components/Button.h"
#include <iostream>
using namespace std;

class ActionTest : public Action {

	virtual void action() override {
		cout << "Hello World";
	}
};

void main() {


	//UIComponent *m = new MessageWindow("A Message", 0, 0, 50, 5, Solid, Orange, Blue);
	//m->draw();

	UIComponent *l = new Label("silencio1234567",5, 5, 15, 7, Double, Blue, Green);
	l->draw();

	ActionTest at;
	Button *button = new Button(&at, "Button", 30, 0, 8, 2, Solid, White, Black);
	button->draw();

	//delete m;

	UIComponent* numBox = new NumericBox(10, 0, 30, 0, 0, Solid, White, Black);
	numBox->draw();

	CCTRL.listenToUserEvents();

	delete l;
	delete button;
	delete numBox;
	getchar();
	CCTRLDESTROY;
}