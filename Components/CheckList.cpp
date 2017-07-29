#include "CheckList.h"


//CheckList::CheckList(string* options, int len, short pos_x, short pos_y, short width, BorderType border, Color tColor, Color bColor, UIComponent* parent)
//	: UIComponent(pos_x, pos_y, width + 3, 2, border, tColor, bColor, parent), drawn(false), mouseEvent(0), current(0) {
//
//	for (int i = 0; i < len; ++i) 
//		list.push_back({ options[i], false });
//	height = list.size() + 1;
//	CCTRL.attachObserver(this);
//}
//
//
//const vector<string> CheckList::getCheckedList() const {
//	
//	vector<string> checked;
//
//	for each (Item item in list)
//		if (item.checked)
//			checked.push_back(item.text);
//	
//	return checked;
//}
//
//
//void CheckList::draw() {
//
//	drawn = true;
//	applyColors();
//	UIComponent::draw();
//	ConsoleController ctrl = CCTRL;
//	COORD c = { position.X+1, position.Y+1 };
//	ctrl.setPosition(c);
//
//	for each (Item item in list)
//	{
//		for (int i = width; i > 0; --i) 
//			putchar(' ');
//
//		ctrl.setPosition(c);
//		drawLine(item);
//		ctrl.setPosition({ c.X, ++c.Y });
//	}
//	postDraw();
//}
//
//
//void CheckList::drawLine(Item item) {
//	COORD c = CCTRL.getPosition();
//	string checkBox = item.checked ? "[x] " : "[ ] ";
//	for (int i = width; i > 0; --i) putchar(' ');
//	CCTRL.setPosition(c);
//	cout << checkBox << item.text.substr(0, width - 4);
//}
//
//
//bool CheckList::checkItem(bool toCheck, int index) {
//
//	if (list.size() < index + 1)
//		return false;
//
//	if (drawn) {
//		applyColors();
//		ConsoleController ctrl = CCTRL;
//		COORD c = { position.X + 2, position.Y + index + 1 };
//		ctrl.setPosition(c);
//
//		char drawChar = toCheck ? 'x' : ' ';
//		if (mouseEvent) {
//			cout << drawChar;
//			mouseEvent = false;
//		}
//		else { // pressed return or space, we want to use the inverted color
//			invertColors(), applyColors();
//			cout << drawChar;
//			invertColors(), applyColors();
//		}
//		CCTRL.setPosition(c);
//	}
//	list[index].checked = toCheck;
//	return true;
//}
//
//
//void CheckList::mouseClicked(MOUSE_EVENT_RECORD ev) {
//	setFocus(true);
//	COORD pos = ev.dwMousePosition;
//
//	if (pos.Y != position.Y && pos.Y != position.Y + height && pos.X != position.X) {
//		
//		mouseEvent = true;
//		current = pos.Y - position.Y - 1;
//		checkItem(!list[current].checked, current);
//	}
//}
//
//
//void CheckList::keyPressed(KEY_EVENT_RECORD keyEvent) {
//
//	switch (keyEvent.wVirtualKeyCode) {
//	case VK_UP:
//		traverse(Up);
//		break;
//	case VK_TAB: 
//		if (current + 1 == list.size()) {
//			CCTRL.setPosition({ position.X + 1, position.Y + static_cast<short>(list.size()) });
//			drawLine(list[list.size() - 1]);
//			current++;
//			break;
//		}
//	case VK_DOWN:
//		traverse(Down);
//		break;
//	case VK_SPACE:
//	case VK_RETURN:
//		if(current < list.size())
//			checkItem(!list[current].checked, current);
//		break;
//	}
//}
//
//
//void CheckList::traverse(Direction direction) {
//
//	if(direction == Down) 
//		current = (++current) % list.size();
//	else 
//		if (--current == -1) current = list.size() - 1;
//
//	CCTRL.setPosition({ position.X + 1, position.Y + current + 1 });
//	invertColors(), applyColors();
//	drawLine(list[current]);
//	invertColors(), applyColors();
//
//	if (direction == Down) {
//		if (current != 0)
//			CCTRL.setPosition({ position.X + 1, position.Y + current });
//		else
//			CCTRL.setPosition({ position.X + 1, position.Y + static_cast<short>(list.size()) });
//		drawLine(list[current - 1 < 0 ? list.size() - 1 : current - 1]);
//	}
//	else {
//		if (current == list.size() - 1)
//			CCTRL.setPosition({ position.X + 1, position.Y + 1 });
//		else
//			CCTRL.setPosition({ position.X + 1, position.Y + current + 2 });
//		drawLine(list[current + 1 == list.size() ? 0 : current + 1]);
//		CCTRL.setPosition({ position.X + width, position.Y + current + 1 });
//	}
//}
//
//
//void CheckList::onFocus() {
//	setFocus(true);
//	CCTRL.setPosition({ position.X + 2, position.Y + 1 });
//}
//
//
//void CheckList::onBlur() {
//	current = -1;
//	setFocus(false);
//	draw();
//}

CheckList::CheckList(string* options, int len, short pos_x, short pos_y, short width, BorderType border, Color tColor, Color bColor, UIComponent* parent)
	: ListComponent(options, len, pos_x, pos_y, width + 4, "[x] ", "[ ] ", border, tColor, bColor, parent),
	selected_items(len, false) {
}

bool CheckList::selectedItem(int index) {
	if (index < 0 || index >= options.size() || selected_items[index]) {
		return false;
	}
	selected_items[index] = true;
	hovered_index = index;
	applyColors();
	draw();
	return true;
}

bool CheckList::clearSelection(int index) {

	if (isChecked(index)) {
		hovered_index = -1;
		selected_items[index] = false;
		draw();
		return true;
	}
	return false;
}

bool CheckList::isChecked(int index) 
{
	return selected_items[index];
}

const vector<string> CheckList::getCheckedStrings() const 
{
	vector<string> current_selected_items;
	for (int i = 0; i < selected_items.size(); i++) 
		if (selected_items[i])
			current_selected_items.push_back(options[i]);
	return current_selected_items;
}

bool CheckList::addSelectedItem(string item)
{
	for (int i = 0; i < options.size(); i++) {
		if (options[i] == item) {
			if (selected_items[i] == false) {
				selected_items[i] = true;
				//hovered_index = index;
				return true;
			}
		}
	}
	return false;
}

bool CheckList::removeSelectedItem(string item)
{
	for (int i = 0; i < options.size(); i++) {
		if (options[i] == item) {
			if (selected_items[i] == true) {
				selected_items[i] = false;
				//hovered_index = index;
				return true;
			}
		}
	}
	return false;
}

bool CheckList::checkItems(vector<int> indexes)
{
	for (int i = 0; i < indexes.size(); i++) {
		if (indexes[i] < 0 || indexes[i] >= options.size())
			return false;
		selected_items[indexes[i]] = true;
	}
	return true;
}
