#include "RadioBox.h"


RadioBox::RadioBox(string* options, int len, short pos_x, short pos_y, short width, BorderType border, Color tColor, Color bColor, UIComponent* parent)
	: UIComponent(pos_x, pos_y, width + 4, 2, border, tColor, bColor, parent), selected_index(-1), hovered_index(-1) {

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
	hovered_index = selected_index;
	applyColors();
	draw();
	return true;
}

bool RadioBox::clearSelection() {

	if (selected_index == -1) {
		return false;
	}
	selected_index = hovered_index =  -1;
	draw();
	return true;
}

void RadioBox::draw() {
	height = static_cast<short> (options.size() + 1);
	UIComponent::draw();
	ConsoleController ctrl = CCTRL;
	COORD c = { position.X + 1, position.Y + 1 };
	ctrl.setPosition(c);

	for (int i = 0; i < options.size(); i++) {
		applyColors();
		for (int i = width; i > 0; --i) putchar(' ');
		ctrl.setPosition(c);
		string checkMark = i == selected_index ? "(x) " : "( ) ";
		invertNeeded(i);
		for (int i = width; i > 0; --i) putchar(' ');
		ctrl.setPosition({ c.X, c.Y });
		cout << checkMark << options.at(i).substr(0, width - 4);
		ctrl.setPosition({ c.X, ++c.Y });
		invertNeeded(i);
		postDraw();
	}
}

void RadioBox::invertNeeded(int i)
{
	if (i == hovered_index) {
		invertColors();
		applyColors();
	}
}

void RadioBox::mouseClicked(MOUSE_EVENT_RECORD mouseEvent) {
	setFocus(true);

	COORD pos = mouseEvent.dwMousePosition;

	if (pos.Y != position.Y && pos.Y != position.Y + height && pos.X != position.X) {
		int index = pos.Y - position.Y - 1;
		if (index == selected_index)
		{
			clearSelection();
		}
		else {
			selectedItem(index);
		}
	}
}

void RadioBox::keyPressed(KEY_EVENT_RECORD keyEvent) {
	switch (keyEvent.wVirtualKeyCode) {
	case VK_UP:
		if (--hovered_index == -1) hovered_index = options.size() - 1;
		CCTRL.setPosition({ position.X + 2, position.Y + hovered_index + 1 });
		break;
	case VK_TAB:
		//TBD
	case VK_DOWN:
		hovered_index = (++hovered_index) % options.size();
		CCTRL.setPosition({ position.X + 2, position.Y + hovered_index + 1 });
		break;
	case VK_SPACE:
	case VK_RETURN:
		if (hovered_index == selected_index)
		{
			int tmpSelectedIndex = selected_index;
			clearSelection();
			hovered_index = tmpSelectedIndex;
		}
		else {
			selectedItem(hovered_index);
		}
		break;
	}
	draw();
}

void RadioBox::onFocus() {
	setFocus(true);
	CCTRL.setCursorVisible(true);	//temporary - Remove it when done drawing lines with color ! Reference to do it : ComboBox.cpp
	CCTRL.setPosition({ position.X + 2, position.Y + 1 + hovered_index });
}

void RadioBox::onBlur() {
	hovered_index = -1;
	setFocus(false);
	draw();
	CCTRL.setCursorVisible(false);	//temporary - Remove it when done drawing lines with color ! Reference to do it : ComboBox.cpp
}