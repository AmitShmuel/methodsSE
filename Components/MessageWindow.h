#pragma once
#include "Button.h"

class MessageWindow : public UIComponent {

private:

	std::string text;
	Button okBtn, cancelBtn;

public:
	MessageWindow(std::string _text, short x_pos = 0, short y_pos = 0, short w = 0, short h = 0,
		BorderType border = Solid, Color tColor = Black, Color bColor = White, UIComponent *parent = NULL);
	
	bool listen();

	void draw() override;
	void addComponent(UIComponent* component) {};
	void removeAll() {};
	~MessageWindow() {};
};