#include "CheckList.h"


CheckList::CheckList(string* options, int len, short pos_x, short pos_y, short width, BorderType border, Color tColor, Color bColor, UIComponent* parent)
	: UIComponent(pos_x, pos_y, width + 3, 2, border, tColor, bColor, parent), drawn(false), mouseEvent(0), current(0) {

	for (int i = 0; i < len; ++i) 
		list.push_back({ options[i], false });

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

	drawn = true;
	applyColors();
	height = list.size() + 1;
	UIComponent::draw();
	ConsoleController ctrl = CCTRL;
	COORD c = { position.X+1, position.Y+1 };
	ctrl.setPosition(c);

	for each (Item item in list)
	{
		for (int i = width; i > 0; --i) 
			putchar(' ');

		ctrl.setPosition(c);
		drawLine(item);
		ctrl.setPosition({ c.X, ++c.Y });
	}
	postDraw();
}

void CheckList::drawLine(Item item) {

	string checkBox = item.checked ? "[x] " : "[ ] ";
	cout << checkBox << item.text.substr(0, width - 4);
}

bool CheckList::checkItem(bool toCheck, int index) {

	if (list.size() < index + 1)
		return false;

	if (drawn) {
		applyColors();
		ConsoleController ctrl = CCTRL;
		COORD c = { position.X + 2, position.Y + index + 1 };
		ctrl.setPosition(c);
		
		char drawChar = toCheck ? 'x' : ' ';
		if (mouseEvent) {
			cout << drawChar;
			mouseEvent = false;
		} 
		else { // pressed return or space, we want to use the inverted color
			invertColors(), applyColors();
			cout << drawChar;
			invertColors(), applyColors();
		}
		CCTRL.setPosition(c);
	}
	list[index].checked = toCheck;
	return true;
}

void CheckList::mouseClicked(MOUSE_EVENT_RECORD ev) {
	setFocus(true);
	COORD pos = ev.dwMousePosition;

	if (pos.Y != position.Y && pos.Y != position.Y + height && pos.X != position.X) {
		
		mouseEvent = true;
		current = pos.Y - position.Y - 1;
		checkItem(!list[current].checked, current);
	}
}

void CheckList::keyPressed(KEY_EVENT_RECORD keyEvent) {

	switch (keyEvent.wVirtualKeyCode) {
	case VK_UP:
		if (--current == -1) current = list.size() - 1;
		CCTRL.setPosition({ position.X + 1, position.Y + current + 1 });
		invertColors(), applyColors();
		drawLine(list[current]);
		invertColors(), applyColors();
		if (current == list.size() - 1)
			CCTRL.setPosition({ position.X + 1, position.Y + 1 });
		else
			CCTRL.setPosition({ position.X + 1, position.Y + current + 2 });
		drawLine(list[current + 1 == list.size() ? 0 : current + 1]);
		break;
	case VK_DOWN:
	case VK_TAB: //should behave the same
		current = (++current) % list.size();
		CCTRL.setPosition({ position.X + 1, position.Y + current + 1 });
		invertColors(), applyColors();
		drawLine(list[current]);
		invertColors(), applyColors();
		if(current != 0)
			CCTRL.setPosition({ position.X + 1, position.Y + current });
		else 
			CCTRL.setPosition({ position.X + 1, position.Y + static_cast<short>(list.size()) });
		drawLine(list[current - 1 < 0 ? list.size() - 1 : current - 1]);
		break;
	case VK_SPACE:
	case VK_RETURN:
		checkItem(!list[current].checked, current);
		break;
	}
}

void CheckList::onFocus() {
	setFocus(true);
	CCTRL.setCursorVisible(true);	//temporary - Remove it when done drawing lines with color ! Reference to do it : ComboBox.cpp
	CCTRL.setPosition({ position.X + 2, position.Y + 1 });
}

void CheckList::onBlur() {
	setFocus(false);
	CCTRL.setCursorVisible(false);	//temporary - Remove it when done drawing lines with color ! Reference to do it : ComboBox.cpp
}