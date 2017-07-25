#include "Label.h"
#include <iostream>

Label::Label(std::string _text, short x_pos, short y_pos, short w, short h, BorderType border,
	Color tColor, Color bColor, UIComponent *parent) : UIComponent(x_pos, y_pos, w, h, border, tColor, bColor), text(_text) {
	if (text.length() > width) text = text.substr(0, width);
}


void Label::draw() {

	UIComponent::draw();
	//ConsoleController ctrl = CCTRL;
	// clear background
	COORD c = { left + 1, top + 1 };
	short text_len = static_cast<short>(text.length());
	short size = width;
	//SetConsoleCursorPosition(h, c);
	//ctrl.setPosition(c);
	GFX.moveTo(c.X, c.Y);
	for (short i = 0; i < size; i++) {
		std::cout << " ";
	}

	// print centered text
	c = { left + 1 + ((width) / 2) - text_len / 2, top + 1 };
	//SetConsoleCursorPosition(h, c);
	//ctrl.setPosition(c);
	GFX.moveTo(c.X, c.Y);
	std::cout << text;
}

void Label::setText(std::string _text) {
	text = _text;
	if (text.length() > width) text = text.substr(0, width);
	draw();
}