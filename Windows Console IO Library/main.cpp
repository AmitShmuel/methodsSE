#include "../Components/Label.h"
#include "../Components/MessageWindow.h"
#include "../Components/NumericBox.h"
#include "../Components/Button.h"
#include "../Components/TextBox.h"
#include "../Components/Components.h"
#include "../Components/CheckList.h"
#include "../Components/RadioBox.h"
#include <iostream>
using namespace std;

class ActionTest : public Action {

	virtual void action() override {
		cout << "Hello World";
	}
};

void main() {

	string* strings = new string[4];
	string* strs = new string[7];
	strings[0] = "one";
	strings[1] = "two";
	strings[2] = "four";
	strings[3] = "five";

	strs[0] = "123456789*+-";
	strs[1] = "two";
	strs[2] = "thrdfghshgsdfgjfsdee";
	strs[3] = "four";
	strs[4] = "five";
	strs[5] = "sixsixsix";
	strs[6] = "sevenblessings";
	
	UIComponent* panel = new Panel(0, 0, CCTRL.getConsoleSize().X - 1, CCTRL.getConsoleSize().Y - 1, Double, White, Black, NULL);
	UIComponent *m = new MessageWindow("A Message", CCTRL.getConsoleSize().X / 2 - 25, CCTRL.getConsoleSize().Y / 2 - 2.5, 50, 5, Solid, Orange, Blue);
	UIComponent* numBox = new NumericBox(10, 0, 30, 0, 0, Solid, White, Black);
	UIComponent *l = new Label("silencio1234567", 5, 5, 15, 7, Double, Blue, Green);
	ActionTest at;
	Button *button = new Button(&at, "Button", 30, 0, 8, 2, Solid, White, Black);
	UIComponent* textBox = new TextBox("Yoav Saroya and messi are friends, we love you man. i think we could be friends forever and ever forever", 170, 25, 5, 20, 5, Dotted, White, Black);
	UIComponent* comboBox = new ComboBox(strings, 4, 50, 0, 10, Double, White, Black);
	CheckList* checkList = new CheckList(strs, 7, 5, 5, 10, Solid, BrightOrange, Blue);
	checkList->checkItem(true, 1);
	checkList->checkItem(true, 4);
	checkList->checkItem(true, 6);
	//textBox->draw();
	panel->addComponent(comboBox);
	panel->addComponent(button);
	panel->addComponent(checkList);
	panel->addComponent(numBox);
	panel->addComponent(l);
	panel->addComponent(m);
	panel->addComponent(textBox);
	
	panel->draw();
	//m->draw();

	//numBox->draw();

	//l->draw();
	//button->draw();
	//checkList->draw();
	//cout << "checked items: " << checkList->getCheckedList().size();

	CCTRL.listenToUserEvents();

	delete[] strs;
	delete[] strings;
	delete panel;
	getchar();
	CCTRLDESTROY;
}