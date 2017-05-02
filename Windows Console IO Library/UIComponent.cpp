#include "UIComponent.h"
#include <iostream>

UIComponent::UIComponent(short x_pos, short y_pos, int w, int h, BorderType border, Color tColor, Color bColor, UIComponent *parent) : parent(parent),
	position { x_pos, y_pos }, width(w), height(h), borderType(border),
	textColor(tColor), backgroundColor(bColor) {
}

UIComponent & UIComponent::getRoot() {
	UIComponent *result = this;
	while (result->parent) {
		result = result->parent;
	}
	return *result;
}

void UIComponent::removeFromScreen() const {
	SetConsoleCursorPosition(h, position);
	SetConsoleTextAttribute(h, 0);
	COORD c = { position.X, position.Y };
	for (short i = 0; i < height + 1; i++) {
		for (short j = 0; j < width + 2; j++) {
			std::cout << " ";
		}
		SetConsoleCursorPosition(h, { c.X, ++c.Y });
	}
}

void UIComponent::draw() {

	drawBorder();
}

void UIComponent::drawBorder() const {
	SetConsoleCursorPosition(h, position);
	SetConsoleTextAttribute(h, textColor | FOREGROUND_INTENSITY | backgroundColor * 16);
	short i;
	COORD c;
	BorderCharacters bc;
	switch (borderType) {
	case DOTTED:
		bc = { '\xDA', '\xBF', '\xC0', '\xD9', '-', '|' };
		break;
	case SOLID:
		bc = { '\xDA', '\xBF', '\xC0','\xD9', '\xC4', '\xB3' };
		break;
	case DBL:
		bc = { '\xC9', '\xBB', '\xC8','\xBC', '\xCD', '\xBA' };
		break;
	case NONE: return;
	default: return;
	}

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