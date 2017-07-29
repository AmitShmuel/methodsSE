#include "RadioBox.h"


RadioBox::RadioBox(string* options, int len, short pos_x, short pos_y, short width, BorderType border, Color tColor, Color bColor, UIComponent* parent)
	: UIComponent(pos_x, pos_y, width + 4, 2, border, tColor, bColor, parent), selected_index(-1) {

	for (int i = 0; i < len; ++i) {
		this->options.push_back(options[i]);
	}

	CCTRL.attachObserver(this);
}

const string RadioBox::getCheckedString() const {

	if (selected_index != -1) {
		return NULL;
	}

	return options.at(selected_index);
}

bool RadioBox::selectedItem(int index) {
	
	if (index < 0 || index >= options.size() || index == selected_index) {
		return false;
	}
	selected_index = index;
	applyColors();
	ConsoleController ctrl = CCTRL;
	COORD c = { position.X + 2, position.Y + 1 };
	COORD originPos = ctrl.getPosition();
	ctrl.setPosition(c);
	for (int i = 0; i < options.size(); i++) {
		string checkMark = i == selected_index ? "x" : " ";
		cout << checkMark;
		ctrl.setPosition({ c.X, ++c.Y });
	}
	ctrl.setPosition(originPos);
	return true;
}

bool RadioBox::clearSelection() {

	if (selected_index == -1) {
		return false;
	}
	selected_index = -1;
	return true;
}

void RadioBox::draw() {
	applyColors();
	height = static_cast<short> (options.size() + 1);
	UIComponent::draw();
	ConsoleController ctrl = CCTRL;
	COORD c = { position.X + 1, position.Y + 1 };
	ctrl.setPosition(c);

	for (int i = 0; i < options.size(); i++) {
		for (int i = width; i > 0; --i) putchar(' ');
		ctrl.setPosition(c);

		string checkMark = i == selected_index ? "[x] " : "[ ] ";
		cout << checkMark << options.at(i).substr(0, width - 4);
		ctrl.setPosition({ c.X, ++c.Y });
	}
	postDraw();
}

void RadioBox::mouseClicked(MOUSE_EVENT_RECORD mouseEvent) {
	setFocus(true);

	COORD pos = mouseEvent.dwMousePosition;

	if (pos.Y != position.Y && pos.Y != position.Y + height && pos.X != position.X) {
		int index = pos.Y - position.Y - 1;
		selectedItem(current = index);
	}
}

void RadioBox::keyPressed(KEY_EVENT_RECORD keyEvent) {
	switch (keyEvent.wVirtualKeyCode) {
	case VK_UP:
		if (--current == -1) current = options.size() - 1;
		CCTRL.setPosition({ position.X + 2, position.Y + current + 1 });
		break;
	case VK_TAB: //should behave the same
	case VK_DOWN:
		current = (++current) % options.size();
		CCTRL.setPosition({ position.X + 2, position.Y + current + 1 });
		break;
	case VK_SPACE:
	case VK_RETURN:
		selectedItem(current);
		break;
	}
}

void RadioBox::onFocus() {
	setFocus(true);
	CCTRL.setCursorVisible(true);	//temporary - Remove it when done drawing lines with color ! Reference to do it : ComboBox.cpp
	CCTRL.setPosition({ position.X + 2, position.Y + 1 + current });
}

void RadioBox::onBlur() {
	setFocus(false);
	CCTRL.setCursorVisible(false);	//temporary - Remove it when done drawing lines with color ! Reference to do it : ComboBox.cpp
}