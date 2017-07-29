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

	string* comboOptions = new string[4];
	comboOptions[0] = "one";
	comboOptions[1] = "two";
	comboOptions[2] = "four";
	comboOptions[3] = "five";

	string* checkListOptions = new string[7];
	checkListOptions[0] = "123456789*+-";
	checkListOptions[1] = "two";
	checkListOptions[2] = "thrdfghshgsdfgjfsdee";
	checkListOptions[3] = "four";
	checkListOptions[4] = "five";
	checkListOptions[5] = "sixsixsix";
	checkListOptions[6] = "sevenblessings";

	string* radioOptions = new string[3];
	radioOptions[0] = "Amit Shmuel";
	radioOptions[1] = "Edan Haoun";
	radioOptions[2] = "Yoav Saroya";

	
	UIComponent* panel = new Panel(0, 0, CCTRL.getConsoleSize().X - 1, CCTRL.getConsoleSize().Y - 1, Double, White, Black, NULL);
	UIComponent *messageWindow = new MessageWindow("A Message", CCTRL.getConsoleSize().X / 2 - 25, CCTRL.getConsoleSize().Y / 2 - 2.5, 50, 5, Solid, Orange, Blue);
	UIComponent* numBox = new NumericBox(10, 0, 30, 0, 0, Solid, White, Black);
	UIComponent *label = new Label("silencio1234567", 5, 15, 15, 7, Double, Blue, Green);
	ActionTest at;
	Button *button = new Button(&at, "Button", 30, 0, 8, 2, Solid, White, Black);
	UIComponent* textBox = new TextBox("Yoav Saroya and messi are friends, we love you man. i think we could be friends forever and ever forever", 170, 25, 3, 30, 6, Dotted, White, Black);
	UIComponent* comboBox = new ComboBox(comboOptions, 4, 50, 0, 10, Double, White, Black);
	CheckList* checkList = new CheckList(checkListOptions, 7, 5, 5, 10, Solid, BrightOrange, Blue);
	checkList->checkItems({ 1, 3, 5 });

	RadioBox* radioBox = new RadioBox(checkListOptions,7,40, 15, 20);


	panel->addComponent(comboBox);
	panel->addComponent(button);
	panel->addComponent(checkList);
	panel->addComponent(numBox);
	panel->addComponent(label);
	panel->addComponent(messageWindow);
	panel->addComponent(textBox);
	panel->addComponent(radioBox);
	
	panel->draw();
	panel->setPosition(5, 7);
	//dynamic_cast<Panel*>(panel)->printMap();

	//m->draw();

	//numBox->draw();

	//l->draw();
	//button->draw();
	//checkList->draw();
	//cout << "checked items: " << checkList->getCheckedList().size();

	CCTRL.listenToUserEvents();

	delete[] comboOptions;
	delete[] checkListOptions;
	delete[] radioOptions;
	delete panel;
	//getchar();
	CCTRLDESTROY;
}