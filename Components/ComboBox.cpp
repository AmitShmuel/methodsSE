#include "ComboBox.h"
#include <iostream>
using namespace std;

ComboBox::ComboBox(string* options, int len, short pos_x, short pos_y, short width, BorderType border, Color tColor, Color bColor, UIComponent* parent) : UIComponent(pos_x, pos_y, width, 2, border, tColor, bColor, parent) ,options(vector<string>()), selected_index(0), open(false) {
	for (int i = 0; i < len; ++i) {
		this->options.push_back(options[i]);
	}
	CCTRL.attachObserver(this);
}

void ComboBox::draw() {
	bool open_down = CCTRL.getConsoleSize().Y > position.Y + options.size() + 1;
	short orig_height = height;
	COORD orig_pos = position;
	short orig_tColor = CCTRL.getTextColor();
	short orig_bColor = CCTRL.getBackgroundColor();
	CCTRL.setColors(this->textColor, false, this->backgroundColor, false);
	if (open) {
		if (open_down) {
			// Box opens downwards
			height += options.size() + 1;
			CCTRL.setPosition({ position.X + 1, position.Y + 1 });
			CCTRL.setColors(this->textColor, true, this->backgroundColor, false);
			cout << this->options.at(selected_index).substr(0, width - 3);
			CCTRL.setColors(this->textColor, false, this->backgroundColor, false);
			CCTRL.setPosition({ position.X + 1, position.Y + 2 });
			for (int i = width; i > 0; --i) putchar('-');
			for (vector<string>::iterator it = options.begin(); it != options.end(); ++it) {
				CCTRL.setPosition({ position.X + 1, position.Y + 3 + static_cast<short>(it - options.begin()) });
				for (int i = width; i > 0; --i) putchar(' ');
				CCTRL.setPosition({ position.X + 1, position.Y + 3 + static_cast<short>(it - options.begin()) });
				cout << it->substr(0, width);
			}
			CCTRL.setPosition({ this->getXPosition() + width - 1 , this->getYPosition() + 1 });
		} else {
			// Box opens upwards
			position.Y = position.Y - options.size() - 1;
			height += options.size() + 1;
			for (vector<string>::iterator it = options.begin(); it != options.end(); ++it) {
				CCTRL.setPosition({ position.X + 1, position.Y + 1 + static_cast<short>(it - options.begin())});
				for (int i = width; i > 0; --i) putchar(' ');
				CCTRL.setPosition({ position.X + 1, position.Y + 1 + static_cast<short>(it - options.begin()) });
				cout << it->substr(0, width);
			}
			CCTRL.setPosition({ position.X + 1, position.Y + height - 2 });
			for (int i = width; i > 0; --i) putchar('-');
			CCTRL.setPosition({ position.X + 1, position.Y + height - 1 });
			CCTRL.setColors(this->textColor, true, this->backgroundColor, false);
			cout << this->options.at(selected_index).substr(0, width - 3);
			CCTRL.setColors(this->textColor, false, this->backgroundColor, false);
			CCTRL.setPosition({ this->getXPosition() + width - 1 , this->getYPosition() + height - 1 });
		}
		
		open_down ? cout << "/\\" : cout << "\\/";
	} else {
		CCTRL.setPosition({ this->getXPosition() + 1 , this->getYPosition() + 1 });
		for (int i = width; i > 0; --i) putchar(' ');
		CCTRL.setPosition({ this->getXPosition() + 1 , this->getYPosition() + 1 });
		cout << this->options.at(selected_index).substr(0, width - 3);
		CCTRL.setPosition({ this->getXPosition() + width - 1 , this->getYPosition() + 1 });
		open_down ? cout << "\\/" : cout << "/\\";
	}
	UIComponent::draw();
	height = orig_height;
	position = orig_pos;
	CCTRL.setColors(orig_tColor, false, orig_bColor, false);
}


void ComboBox::mouseClicked(MOUSE_EVENT_RECORD e) {
	if (CCTRL.isIntersects(e.dwMousePosition, this)) {
		this->toggle();
	}
}

void ComboBox::toggle() {
	open = !open; 
	if (open) {
		this->draw();
	} else {
		bool open_down = CCTRL.getConsoleSize().Y > position.Y + options.size() + 1;
		if (open_down) {
			CCTRL.setPosition(position);
		} else {
			for (short i = 0; i < options.size() + 1; ++i) {
				CCTRL.setPosition({ position.X, position.Y - static_cast<short>(options.size()) - 1 + i });
				for (short j = width + 2; j > 0; --j) putchar(' ');
			}
		}
		
		
		this->getRoot().draw();
	}
}

ComboBox::~ComboBox() {
	CCTRL.detachObserver(this);
}
