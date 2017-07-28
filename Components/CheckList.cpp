#include "CheckList.h"


CheckList::CheckList(string* options, int len, short pos_x, short pos_y, short width, BorderType border, Color tColor, Color bColor, UIComponent* parent)
	: UIComponent(pos_x, pos_y, width + 3, 2, border, tColor, bColor, parent), drawn(false), current(0) {

	for (int i = 0; i < len; ++i) {
		list.push_back({ options[i], false });
	}

	CCTRL.attachObserver(this);
}

const vector<string> CheckList::getCheckedList() const {
	
	vector<string> checked;

	for each (Item item in list)
		if (item.checked)
			checked.push_back(item.text);
	
	return checked;
}

void CheckList::draw() {
	applyColors();
	drawn = true;
	height = list.size() + 1;
	UIComponent::draw();
	ConsoleController ctrl = CCTRL;
	COORD c = { position.X+1, position.Y+1 };
	ctrl.setPosition(c);

	for each (Item item in list)
	{
		for (int i = width; i > 0; --i) putchar(' ');
		ctrl.setPosition(c);

		string checkBox = item.checked ? "[x] " : "[ ] ";
		cout << checkBox << item.text.substr(0, width - 4);
		ctrl.setPosition({ c.X, ++c.Y });
	}

	postDraw();
}

bool CheckList::checkItem(bool toCheck, int index) {

	if (list.size() < index + 1)
		return false;

	if (drawn) {
		applyColors();
		ConsoleController ctrl = CCTRL;
		COORD c = { position.X + 2, position.Y + index + 1 };
		ctrl.setPosition(c);

		if (toCheck)
			cout << 'x';
		else
			cout << ' ';
		CCTRL.setPosition(c);
	}

	return list[index].checked = toCheck;
}

void CheckList::mouseClicked(MOUSE_EVENT_RECORD mouseEvent) {
	setFocus(true);
	COORD pos = mouseEvent.dwMousePosition;

	if (pos.Y != position.Y && pos.Y != position.Y + height && pos.X != position.X) {
		
		current = pos.Y - position.Y - 1;
		checkItem(!list[current].checked, current);
	}
}

void CheckList::keyPressed(KEY_EVENT_RECORD keyEvent) {
	switch (keyEvent.wVirtualKeyCode) {
	case VK_UP:
		if (--current == -1) current = list.size() - 1;
		CCTRL.setPosition({ position.X + 2, position.Y + current + 1 });
		break;
	case VK_TAB: //should behave the same
	case VK_DOWN:

		current = (++current) % list.size();
		CCTRL.setPosition({ position.X + 2, position.Y + current + 1 });
		break;
	case VK_SPACE:
	case VK_RETURN:
		checkItem(!list[current].checked, current);
		break;
	}
}

void CheckList::onFocus() {
	setFocus(true);
	CCTRL.setPosition({ position.X + 2, position.Y + 1 });
	CCTRL.setCursorVisible(true);	//temporary - Remove it when done drawing lines with color ! Reference to do it : ComboBox.cpp
}

void CheckList::onBlur() {
	setFocus(false);
	CCTRL.setCursorVisible(false);	//temporary - Remove it when done drawing lines with color ! Reference to do it : ComboBox.cpp
}