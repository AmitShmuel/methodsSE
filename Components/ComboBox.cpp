#include "ComboBox.h"
#include <iostream>
using namespace std;

ComboBox::ComboBox(ComboBox * o) : UIComponent(o->position.X, o->position.Y, o->width, 2, o->borderType, o->textColor, o->backgroundColor, o->parent), _originalState(NULL), options(NULL), selected_index(-1), open_down(o->open_down), open(false) {}

ComboBox::ComboBox(string* options, int len, short pos_x, short pos_y, short width, BorderType border, Color tColor, Color bColor, UIComponent* parent) : UIComponent(pos_x, pos_y, width, 2, border, tColor, bColor, parent) ,options(vector<string>()), selected_index(-1), open(false) {
	for (int i = 0; i < len; ++i) {
		this->options.push_back(options[i]);
	}
	open_down = CCTRL.getConsoleSize().Y > position.Y + this->options.size() + 1;
	_originalState = new ComboBox(this);
	CCTRL.attachObserver(this);
}

void ComboBox::draw() {
	/*short orig_height = height;
	COORD orig_pos = position;*/
	short orig_tColor = CCTRL.getTextColor();
	short orig_bColor = CCTRL.getBackgroundColor();
	CCTRL.setColors(this->textColor, false, this->backgroundColor, false);
	if (open) {
		if (open_down) {
			// Box opens downwards
			//height += options.size() + 1;
			CCTRL.setPosition({ position.X + 1, position.Y + 1 });
			CCTRL.setColors(this->textColor, true, this->backgroundColor, false);
			if (selected_index != -1)
				cout << this->options.at(selected_index).substr(0, width - 3);
			CCTRL.setColors(this->textColor, false, this->backgroundColor, false);
			CCTRL.setPosition({ position.X + 1, position.Y + 2 });
			for (int i = width; i > 0; --i) putchar('-');
			for (vector<string>::iterator it = options.begin(); it != options.end(); ++it) {
				if (it - options.begin() == selected_index) invertColors(), applyColors();
				CCTRL.setPosition({ position.X + 1, position.Y + 3 + static_cast<short>(it - options.begin()) });
				for (int i = width; i > 0; --i) putchar(' ');
				CCTRL.setPosition({ position.X + 1, position.Y + 3 + static_cast<short>(it - options.begin()) });
				cout << it->substr(0, width);
				if (it - options.begin() == selected_index) invertColors(), applyColors();
			}
			CCTRL.setPosition({ this->getXPosition() + width - 1 , this->getYPosition() + 1 });
		} else {
			// Box opens upwards
			//position.Y = position.Y - options.size() - 1;
			//height += options.size() + 1;
			for (vector<string>::iterator it = options.begin(); it != options.end(); ++it) {
				if (it - options.begin() == selected_index) invertColors(), applyColors();
				CCTRL.setPosition({ position.X + 1, position.Y + 1 + static_cast<short>(it - options.begin())});
				for (int i = width; i > 0; --i) putchar(' ');
				CCTRL.setPosition({ position.X + 1, position.Y + 1 + static_cast<short>(it - options.begin()) });
				cout << it->substr(0, width);
				if (it - options.begin() == selected_index) invertColors(), applyColors();

			}
			CCTRL.setPosition({ position.X + 1, position.Y + height - 2 });
			for (int i = width; i > 0; --i) putchar('-');
			CCTRL.setPosition({ position.X + 1, position.Y + height - 1 });
			CCTRL.setColors(this->textColor, true, this->backgroundColor, false);
			if (selected_index != -1)
				cout << this->options.at(selected_index).substr(0, width - 3);
			CCTRL.setColors(this->textColor, false, this->backgroundColor, false);
			CCTRL.setPosition({ this->getXPosition() + width - 1 , this->getYPosition() + height - 1 });
		}
		
		open_down ? cout << "/\\" : cout << "\\/";
	} else {
		CCTRL.setPosition({ this->getXPosition() + 1 , this->getYPosition() + 1 });
		for (int i = width; i > 0; --i) putchar(' ');
		CCTRL.setPosition({ this->getXPosition() + 1 , this->getYPosition() + 1 });
		if (selected_index != -1)
			cout << this->options.at(selected_index).substr(0, width - 3);
		CCTRL.setPosition({ this->getXPosition() + width - 1 , this->getYPosition() + 1 });
		open_down ? cout << "\\/" : cout << "/\\";
	}
	UIComponent::draw();
	//height = orig_height;
	//position = orig_pos;
	CCTRL.setColors(orig_tColor, false, orig_bColor, false);
}


void ComboBox::mouseClicked(MOUSE_EVENT_RECORD e) {
	//open_down = CCTRL.getConsoleSize().Y > position.Y + options.size() + 1;

	if (open) {
		if (CCTRL.isIntersects(e.dwMousePosition, this->_originalState)) {
			if (e.dwMousePosition.X > this->_originalState->position.X
				&& e.dwMousePosition.X < this->_originalState->position.X + this->_originalState->width
				&& e.dwMousePosition.Y > this->_originalState->position.Y
				&& e.dwMousePosition.Y < this->_originalState->position.Y + this->_originalState->height) {
				this->toggle();
			}
		} else if (CCTRL.isIntersects(e.dwMousePosition, this) 
			&& e.dwMousePosition.X > position.X 
			&& e.dwMousePosition.X < position.X + width
			&& e.dwMousePosition.Y > position.Y
			&& e.dwMousePosition.Y < position.Y + height) {
			if (open_down) {
				selected_index = e.dwMousePosition.Y - position.Y - 3;
			} else {
				selected_index = e.dwMousePosition.Y - position.Y - 1;
			}
			this->toggle();
		}
	}
	else {
		if (CCTRL.isIntersects(e.dwMousePosition, this)
			&& e.dwMousePosition.X > position.X
			&& e.dwMousePosition.X < position.X + width
			&& e.dwMousePosition.Y > position.Y
			&& e.dwMousePosition.Y < position.Y + height) {
			this->toggle();
		}
	}
}

void ComboBox::keyPressed(KEY_EVENT_RECORD e) {
	switch (e.wVirtualKeyCode) {
	case VK_UP:
	case VK_NUMPAD8:
		if (this->open && this->selected_index > 0)
			this->selected_index--;
		break;
	case VK_DOWN:
	case VK_NUMPAD2:
		if (this->open && this->selected_index + 1 < this->options.size())
			this->selected_index++;
		break;
	case VK_RETURN:
	case VK_SPACE:
		cout << "enter?";
		break;
	default:
		break;
	}
	this->draw();
}

void ComboBox::toggle() {
	open = !open; 
	if (open) {
		height += options.size() + 1;
		if (!open_down) {
			position.Y = position.Y - options.size() - 1;
		}
		this->draw();
	} else {
		height = _originalState->height;
		position = _originalState->position;
		if (open_down) {
			for (short i = 0; i < options.size() + 1; ++i) {
				CCTRL.setPosition({ position.X, position.Y + 3 + i });
				for (short j = width + 2; j > 0; --j) putchar(' ');
			}
		} else {
			for (short i = 0; i < options.size() + 1; ++i) {
				CCTRL.setPosition({ position.X, position.Y - static_cast<short>(options.size()) - 1 + i });
				for (short j = width + 2; j > 0; --j) putchar(' ');
			}
		}
		
		
		this->getRoot().draw();
	}
}

string ComboBox::getValue() const {
	return selected_index != -1 ? this->options.at(selected_index) : "No item selected";
}

ComboBox::~ComboBox() {
	CCTRL.detachObserver(this);
	if (_originalState) delete _originalState;
}
