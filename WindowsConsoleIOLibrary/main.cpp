#include "../Components/Label.h"
#include "../Common/Graphics.h"
#include "../Components/Button.h"
#include "../Common/Action.h"
#include <iostream>
using namespace std;

class ActionTest : public Action {

	virtual void action() override {
		cout << "Hello World";
	}
};

void main() {
	//Graphics g = Graphics();
	//GFX.setBackground(Blue);
	//GFX.clearScreen();
	//UIComponent *l = new Label("Silencio1234567",0, 0, 50, 2, Double, BrightOrange, Color::BrightRed);
	//l->draw();
	//delete l;
	//GFX.clearScreen();
	ActionTest at;
	Button *button = new Button(&at, "Silencio1234567", 0, 0, 10, 3, Solid, Black, Black);
	button->draw();
	//button->click();
	delete button;
	getchar();
	GFX_DESTROY;

}