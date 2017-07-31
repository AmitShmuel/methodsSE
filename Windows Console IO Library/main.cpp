#include "../Components/Label.h"
#include "../Components/MessageWindow.h"
#include "../Components/NumericBox.h"
#include "../Components/Button.h"
#include "../Components/TextBox.h"
#include "../Components/Components.h"
#include "../Components/CheckList.h"
#include "../Components/RadioBox.h"
#include <iostream>
#include <thread>
using namespace std;

static Label* msgDisplay;

class ActionTest : public Action {

	virtual void action() override {
		CreateThread(NULL, 0, submitForm, NULL, 0, NULL);
	}
	static DWORD WINAPI submitForm(LPVOID lpParam) {
		CCTRL.messageDialog("Are You Sure You Want To Submit ?", Double);
		while (CCTRL.getLastMessageResponse() == -1 && msgDisplay != NULL);
		if (CCTRL.getLastMessageResponse() == 1) {
			msgDisplay->setVisible(true);
		}
		else {
			msgDisplay->setVisible(false);
		}
		CCTRL.resetLastMessage();
		return 1;
	}
};

void main() {
	
	string gender[]  = { "Male", "Female" };
	string hobbies[] = { "Playing PC Games", "Watching TV", "Sport", "Sleep", "Listening to music", "Playing Guitar" };
	string colors[]  = {"Black", "White", "Green", "Red", "Yellow", "Blue", "Pink", "Orange"};

	UIComponent* panel = new Panel(0, 0, CCTRL.getConsoleSize().X - 1, CCTRL.getConsoleSize().Y - 3 , Double, White, Black, NULL);
	UIComponent* headlineLabel = new Label("Please Fill Out Your Personal Details", CCTRL.getConsoleSize().X / 3 - 6, 0, 39, 2, Dotted, Green, Black);

	UIComponent* fullNameLabel = new Label("Full Name: ", 0, 3, 10, 2);
	UIComponent* fullNameInput = new TextBox("", 18, 11, 3, 20, 2, Solid, White, Black);

	UIComponent* ageLabel	   = new Label("Age: ", 35, 3, 10, 2);
	UIComponent* ageInput	   = new NumericBox(18, 10, 100, 45, 3, Solid, White, Black);

	UIComponent* genderLabel   = new Label("Gender: ", 0, 6, 10, 2);
	UIComponent* genderInput   = new RadioBox(gender, 2, 11, 6, 12, Solid, White, Black);

	UIComponent* hobbiesLabel  = new Label("Hobbies: ", 35, 6, 10, 2);
	UIComponent* hobbiesInput  = new CheckList(hobbies, 6, 45, 6, 15, Solid, White, Black);

	UIComponent* colorsLabel   = new Label("Fav Color: ", 0, 10, 10, 2);
	UIComponent* colorsInput   = new ComboBox(colors, 8, 11, 10, 15, Solid, White, Black);

	UIComponent* resultLabel   = new Label("Form Submitted", CCTRL.getConsoleSize().X / 2 - 7, 22, 14, 2, Dotted, BrightPurple, Black);
	msgDisplay = dynamic_cast<Label*>(resultLabel);
	ActionTest submitAction;
	UIComponent* submitButton  = new Button(&submitAction, "Submit", CCTRL.getConsoleSize().X / 2 - 6, 15, 10, 2, Double, Red, Black);

	panel->addComponent(headlineLabel);
	panel->addComponent(fullNameLabel);
	panel->addComponent(fullNameInput);
	panel->addComponent(ageLabel);
	panel->addComponent(ageInput);
	panel->addComponent(genderLabel);
	panel->addComponent(genderInput);
	panel->addComponent(hobbiesLabel);
	panel->addComponent(hobbiesInput);
	panel->addComponent(colorsLabel);
	panel->addComponent(colorsInput);
	panel->addComponent(submitButton);
	CCTRL.setView(panel);
	CCTRL.listenToUserEvents();
	delete panel;
	CCTRLDESTROY;
}