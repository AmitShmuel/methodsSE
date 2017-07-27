#include "TextBox.h"

TextBox::TextBox(std::string _text, int _maxSize, short x_pos, short y_pos, short w, short h, BorderType border,
	Color tColor, Color bColor, UIComponent *parent) : UIComponent(x_pos, y_pos, w, h, border, tColor, bColor), text(_text), maxSize(_maxSize) {
	if (text.length() > width * height)   text = text.substr(0, width * height);
	if (text.length() > maxSize) text = text.substr(0, maxSize);
	CCTRL.attachObserver(this);
}

TextBox::~TextBox() {
	CCTRL.detachObserver(this);
}

void TextBox::mouseClicked(MOUSE_EVENT_RECORD mouseRecord) {
	COORD mousePos = mouseRecord.dwMousePosition;
	if (mousePos.Y > getYPosition() &&
		mousePos.Y < getYPosition() + getHeight() &&
		mousePos.X > getXPosition() &&
		mousePos.X < getXPosition() + getWidth() + 1) {

		if (mousePos.Y > lastIndexPosition.Y ||
			(mousePos.Y == lastIndexPosition.Y &&
				mousePos.X > lastIndexPosition.X)) {
			CCTRL.setPosition(lastIndexPosition);
		}
		else CCTRL.setPosition(mousePos);

	}
}

void TextBox::keyPressed(KEY_EVENT_RECORD key) {
	switch (key.wVirtualKeyCode) {
	case VK_UP:

		break;
	}
}

void TextBox::setText(std::string _text) {
	text = _text;
	if (text.length() > width * height) text = text.substr(0, width * height);
	if (text.length() > maxSize) text = text.substr(0, maxSize);
	this->draw();
}

void TextBox::draw() {

	UIComponent::draw();
	ConsoleController ctrl = CCTRL;
	// clear background
	COORD c = { position.X + 1, position.Y + 1 };
	short text_len = static_cast<short>(text.length());
	ctrl.setPosition(c);
	//GFX.moveTo(c.X, c.Y);
	for (short i = 0; i < height; i++) {
		for (short j = 0; j < width; j++) {
			std::cout << " ";
		}
		ctrl.setPosition({ position.X + 1, position.Y + i + 1 });
	}

	c = { position.X + 1, position.Y + 1 };
	ctrl.setPosition(c);

	std::stringstream ss(text);
	std::istream_iterator<std::string> begin(ss);
	std::istream_iterator<std::string> end;
	std::vector<std::string> vstrings(begin, end);
	for (auto string : vstrings) {
		auto currPos = ctrl.getPosition();
		if (position.Y + height == currPos.Y + 1 &&
			currPos.X + string.length() + 1 > position.X + width) {
			break;
		}

		if (currPos.X + string.length() + 1 > position.X + width ) {
			ctrl.setPosition({ position.X + 1, currPos.Y + 1 });
		}
		std::cout << string;
		lastIndexPosition = ctrl.getPosition();
		std::cout << " ";
	}
	//std::cout << text;
}