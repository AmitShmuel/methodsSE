#include "NumericBox.h"
#include <string>


NumericBox::NumericBox(int _val,int _min, int _max, short x_pos, short y_pos, int w, int h, BorderType border, Color tColor, Color bColor, UIComponent* parent):
		UIComponent(x_pos, y_pos, w, h, border, tColor, bColor, parent) {
	setMax(_max);
	setMin(_min);
	setValue(_val);
}

void NumericBox::drawValue() const {
	auto ctrl = CCTRL;
	// clear background
	COORD c = { position.X + 2, position.Y + 1 };
	short text_len = static_cast<short>(std::to_string(getValue()).length());
	int size = width;
	//SetConsoleCursorPosition(h, c);
	ctrl.setPosition(c);
	for (short i = 0; i < size-2; i++) {
		std::cout << " ";
	}

	// print centered text
	c = { position.X + static_cast<short>((width) / 2) - text_len / 2, position.Y + 1 };
	//SetConsoleCursorPosition(h, c);
	ctrl.setPosition(c);
	std::cout << getValue();
}

void NumericBox::drawOperators() const {
	auto ctrl = CCTRL;
	COORD c = { position.X + 1, position.Y + 1 };
	ctrl.setPosition(c);
	std::cout << "-";
	c = { static_cast<short>(width) - position.X, position.Y + 1 };
	ctrl.setPosition(c);
	std::cout << "+";
	/*
	BorderCharacters bc;
	switch(this->getBorderType()) {
	case DOTTED:
		bc = { '\xDA', '\xBF', '\xC0', '\xD9', '-', '|' };
		break;
	case SOLID:
		bc = { '\xDA', '\xBF', '\xC0','\xD9', '\xC4', '\xB3' };
		break;
	case DBL:
		bc = { '\xC9', '\xBB', '\xC8','\xBC', '\xCD', '\xBA' };
		break;
	case NONE:
		break;
	default: break;
	}
	c = { position.X + 2, position.Y / 2 + 1 };
	ctrl.setPosition(c);
	std::cout << bc.vertical;
	*/
}


void NumericBox::draw() {
	UIComponent::draw();
	drawOperators();
	drawValue();
}

void NumericBox::setValue(int _val) {
	//value = _val >= getMin() && _val <= getMax() ? _val : (getMin() + getMax())/2 ;
	if(_val >= getMin() && _val <= getMax()) {
		value = _val;
		drawValue();
	}
	else {
		throw IOConsoleException("Numeric Box: value exceeds limits");
	}
}

void NumericBox::setMin(int _min) {
	//minimum = (getValue() < _min ? getValue() : _min);
	if(getValue() >= _min) {
		minimum = _min;
	}
	else {
		throw IOConsoleException("Numeric Box: value exceeds limits");
	}
}

void NumericBox::setMax(int _max) {
	//maximum = (getValue() > _max ? getValue() : _max);
	if(getValue() <= _max) {
		maximum = _max;
	}
	else {
		throw IOConsoleException("Numeric Box: value exceeds limits");
	}
}

void NumericBox::increment() {
	setValue(getValue() + 1);
}

void NumericBox::decrement() {
	setValue(getValue() - 1);
}