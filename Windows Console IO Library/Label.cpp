#include "Label.h"

Label::Label(std::string _text, short x_pos, short y_pos, int w, int h, BorderType border,
	Color tColor, Color bColor):Component(x_pos, y_pos, w, h, border, tColor, bColor), text(_text) {}

void Label::drawBorder(COORD c, BorderCharacters& bc) const {

	short i;
	printf("%c", bc.leftTopCorner);

	for (i = 0; i < width; i++)
		printf("%c", bc.horizontal);

	printf("%c", bc.rightTopCorner);

	for (i = 1; i < height; i++) {
		c = { position.X, position.Y + i };
		SetConsoleCursorPosition(h, c);
		printf("%c", bc.vertical);
		c = { position.X + static_cast<short>(width) + 1, position.Y + i };
		SetConsoleCursorPosition(h, c);
		printf("%c", bc.vertical);
	}

	c = { position.X, position.Y + i };
	SetConsoleCursorPosition(h, c);
	printf("%c", bc.leftBottomCorner);
	for (i = 0; i < width; i++) {
		printf("%c", bc.horizontal);
	}
	printf("%c", bc.rightBottomCorner);
}

void Label::draw() {
	SetConsoleCursorPosition(h, position);
	SetConsoleTextAttribute(h, textColor | FOREGROUND_INTENSITY | backgroundColor * 16);
	COORD c{};
	BorderCharacters bc = {};
		//TODO: Decide on characters which will represents the DOTTED border
		switch (borderType) {
		case DOTTED:
			bc = { '\0', '\0', '\0', '\0', '\0', '\0' };
			drawBorder(c, bc);
			break;
		case SOLID:
			bc = { '\xDA', '\xBF', '\xC0','\xD9', '\xC4', '\xB3' };
			drawBorder(c, bc);
			break;
		case NONE:
		default: break;
	}
	c = { position.X+1, position.Y + 1 };
	SetConsoleCursorPosition(h, c);
	std::cout << text;

	c = { position.X + static_cast<short>(text.length()+1), position.Y + 1 };
	SetConsoleCursorPosition(h, c);

	int size = width - static_cast<short>(text.length());
	for(short i =0; i < size; i++) {
		std::cout << " ";
	}
}

void Label::removeFromScreen() {	//TODO
	
}
