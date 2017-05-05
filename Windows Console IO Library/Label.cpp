#include "Label.h"
#include <iostream>

Label::Label(std::string _text, short x_pos, short y_pos, int w, int h, BorderType border,
	Color tColor, Color bColor, UIComponent *parent) : UIComponent(x_pos, y_pos, w, h, border, tColor, bColor, parent), text(_text) {
	if (text.length() > width) text = text.substr(0, width);
}


void Label::draw() {

	UIComponent::draw();
	ConsoleController ctrl = CCTRL;
	// clear background
	COORD c = { position.X + 1, position.Y + 1 };
	short text_len = static_cast<short>(text.length());
	int size = width;
	//SetConsoleCursorPosition(h, c);
	ctrl.setPosition(c);
	for (short i = 0; i < size; i++) {
		std::cout << " ";
	}

	// print centered text
	c = { position.X + 1 + static_cast<short>((width) / 2) - text_len / 2, position.Y + 1 };
	//SetConsoleCursorPosition(h, c);
	ctrl.setPosition(c);
	std::cout << text;
	

}