#include "CheckList.h"


CheckList::CheckList(string* options, int len, short pos_x, short pos_y, short width, BorderType border, Color tColor, Color bColor, UIComponent* parent) 
	: UIComponent(pos_x, pos_y, width+3, 2, border, tColor, bColor, parent) {

	for (int i = 0; i < len; ++i) {
		list.push_back({ options[i], false });
	}

	CCTRL.attachObserver(this);
}

const vector<CheckList::Item> CheckList::getCheckedList() const {
	
	vector<Item> checked = vector<Item>();

	for each (Item item in list)
		if (item.checked)
			checked.push_back(item);
	
	return checked;
}

bool CheckList::checkItem(int index) {

	if (list.size() < index+1)
		return false;

	return list[index].checked = true;
}

bool CheckList::uncheckItem(int index) {

	if (list.size() < index + 1)
		return false;

	return !(list[index].checked = false);
}

void CheckList::draw() {

	height = list.size() + 1;
	UIComponent::draw();
	ConsoleController ctrl = CCTRL;
	COORD c = { position.X+1, position.Y+1 };
	ctrl.setPosition(c);

	for each (Item item in list)
	{
		for (int i = width; i > 0; --i) putchar(' ');
		ctrl.setPosition(c);

		string s = item.checked ? "[x] " : "[ ] ";
		cout << s << item.text.substr(0, width - 4);
		ctrl.setPosition({ c.X, ++c.Y });
	}
}