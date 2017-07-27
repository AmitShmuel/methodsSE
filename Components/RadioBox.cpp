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

bool RadioBox::slectedItem(int index) {
	
	if (index < 0 || index >= options.size() || index == selected_index) {
		return false;
	}
	selected_index = index;
	draw();
	return true;
}

bool RadioBox::clearSelection() {

	if (selected_index == -1) {
		return false;
	}
	selected_index = -1;
	draw();
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

	COORD pos = mouseEvent.dwMousePosition;

	if (pos.Y != position.Y && pos.Y != position.Y + height && pos.X != position.X) {
		int index = pos.Y - position.Y - 1;
		clearSelection();
		slectedItem(index);
		
		draw();
		COORD c = { position.X + 2, position.Y + index + 1 };
		CCTRL.setPosition(c);
	}
}
