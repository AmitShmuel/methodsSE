#include "NumericBox.h"

NumericBox::NumericBox(int _val, int _min, int _max, short x_pos, short y_pos, int w, int h,
	BorderType border, Color tColor, Color bColor, UIComponent * parent)
	: UIComponent(x_pos, y_pos, w, h, border, tColor, bColor, parent), incrementor(*this), decrementor(*this) {

	if (_val >= _min && _val <= _max) {
		maximum = _max;
		minimum = _min;
		value = _val;
	}
	else {
		throw IOConsoleException("Numeric Box: value exceeds limits");
	}
}

void NumericBox::drawValue() const {
	//auto ctrl = CCTRL;
	//// clear background
	//COORD c = { position.X + 2, position.Y + 1 };
	//short text_len = static_cast<short>(std::to_string(getValue()).length());
	//int size = width;
	////SetConsoleCursorPosition(h, c);
	//ctrl.setPosition(c);
	//for (short i = 0; i < size - 2; i++) {
	//	std::cout << " ";
	//}

	//// print centered text
	//c = { position.X + static_cast<short>((width) / 2) - text_len / 2, position.Y + 1 };
	////SetConsoleCursorPosition(h, c);
	//ctrl.setPosition(c);
	//std::cout << getValue();
}

void NumericBox::drawOperators() const {
	//auto ctrl = CCTRL;
	//COORD c = { position.X + 1, position.Y + 1 };
	//ctrl.setPosition(c);
	//std::cout << "-";
	//c = { static_cast<short>(width) - position.X, position.Y + 1 };
	//ctrl.setPosition(c);
	//std::cout << "+";
}

void NumericBox::draw() {
	UIComponent::draw();
	drawOperators();
	drawValue();
}

void NumericBox::setValue(int _val) {
	if (_val < getMin()) value = getMin();
	else if (_val > getMax()) value = getMax();
	else value = _val;
	drawValue();
}

void NumericBox::setMin(int _min) {
	if (getValue() >= _min) {
		minimum = _min;
	}
	else {
		throw IOConsoleException("Numeric Box: value exceeds limits");
	}
}

void NumericBox::setMax(int _max) {
	if (getValue() <= _max) {
		maximum = _max;
	}
	else {
		throw IOConsoleException("Numeric Box: value exceeds limits");
	}
}

NumericBox::~NumericBox() {
	if (incrementButton) delete incrementButton;
	if (decrementButton) delete decrementButton;
}

void NumericBox::IncrementAction::action() {
	parent.setValue(parent.getValue() + 1);
}

void NumericBox::DecrementAction::action() {
	parent.setValue(parent.getValue() - 1);
}