#include "Label.h"

Label::Label(std::string _text, short x_pos, short y_pos, int w, int h, BorderType border,
	Color tColor, Color bColor):UIComponent(x_pos, y_pos, w, h, border, tColor, bColor), text(_text) {}


void Label::draw() {

	UIComponent::draw();

	COORD c = { position.X+1, position.Y + 1 };
	SetConsoleCursorPosition(h, c);
	std::cout << text;

	c = { position.X + static_cast<short>(text.length()+1), position.Y + 1 };
	SetConsoleCursorPosition(h, c);

	//Filling the background
	int size = width - static_cast<short>(text.length());
	for(short i =0; i < size; i++) {
		std::cout << " ";
	}
}