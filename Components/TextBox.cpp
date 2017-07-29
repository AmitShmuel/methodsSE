#include "TextBox.h"

TextBox::TextBox(std::string _text, int _maxSize, short x_pos, short y_pos, short w, short h, BorderType border,
	Color tColor, Color bColor, UIComponent *parent) : UIComponent(x_pos, y_pos, w, h, border, tColor, bColor), text(_text), maxSize(_maxSize) {
	if (text.length() > width * height)   text = text.substr(0, width * height);
	if (text.length() > maxSize) text = text.substr(0, maxSize);
	//CCTRL.attachObserver(this);
}

TextBox::~TextBox() {
	CCTRL.detachObserver(this);
}

void TextBox::mouseClicked(MOUSE_EVENT_RECORD mouseRecord) {
	CCTRL.setCursorVisible(true);
	setFocus(true);
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
	auto ctrl = CCTRL;
	COORD currPos = ctrl.getPosition();
	int indexToDelete = 0;
	switch (key.wVirtualKeyCode) {
	case VK_UP:
		if (currPos.Y != position.Y + 1)
			ctrl.setPosition({ currPos.X, currPos.Y - 1 });
		break;
	case VK_LEFT:
		if (currPos.X != position.X + 1)
			ctrl.setPosition({ currPos.X - 1, currPos.Y});
		break;
	case VK_DOWN:
		if (currPos.Y != position.Y + height - 1) {
			if (currPos.Y == lastIndexPosition.Y  || currPos.Y + 1 == lastIndexPosition.Y && currPos.X > lastIndexPosition.X ) {
				ctrl.setPosition(lastIndexPosition);
			}
			else ctrl.setPosition({ currPos.X, currPos.Y + 1 });
		}
		break;
	case VK_RIGHT:
		if (currPos.X != position.X + width) {
			if (currPos.Y == lastIndexPosition.Y && currPos.X == lastIndexPosition.X) {
				ctrl.setPosition(lastIndexPosition);
			}
			else ctrl.setPosition({ currPos.X + 1, currPos.Y });

		}
		break;

	case VK_HOME:
		ctrl.setPosition({ position.X + 1, currPos.Y });
		break;
		
	case VK_END:
		ctrl.setPosition({ lastIndexPosition.Y == currPos.Y ?  lastIndexPosition.X : position.X + width , currPos.Y });
		break;

	case VK_BACK:
		indexToDelete = (currPos.Y - position.Y - 1)*(width)+ currPos.X - position.X - 1;
		if (indexToDelete == 0) break;
		while (indexToDelete - 1 > text.size()) indexToDelete--;
		text.erase(indexToDelete - 1, 1);
		draw();
		if (currPos.X - 1 == position.X) {
			ctrl.setPosition({ position.X + width,currPos.Y - 1 });
		}
		else ctrl.setPosition({currPos.X - 1,currPos.Y});
		break;

	case VK_DELETE:
		//std::cout << " ";
		////text.erase(currPos.X + currPos.Y, 1);	//Need to know which character to delete, and then it's complete
		//ctrl.setPosition({ currPos.X + 1, currPos.Y });
		//currPos = ctrl.getPosition();
		//if (currPos.X == position.X + width + 1) {
		//	if (currPos.Y == lastIndexPosition.Y) ctrl.setPosition({ currPos.X - 1 ,currPos.Y});
		//	else ctrl.setPosition({ position.X + 1  ,currPos.Y + 1 });
		//}
		////draw();
		//break;
		indexToDelete = (currPos.Y - position.Y - 1)*(width)+currPos.X - position.X - 1;
		//for (int i = indexToDelete; i % width != 0; i++) {
		//	if (text[i] != ' ') {
		//		indexToDelete = (currPos.Y - position.Y)*(width)+position.X - 1;
		//		break;
		//	}
		//}
		text.erase(indexToDelete, 1);
		draw();
		ctrl.setPosition({ currPos.X,currPos.Y });
		break;

	default: 
		WORD currCharacter = key.wVirtualKeyCode;
		indexToDelete = (currPos.Y - position.Y - 1)*(width)+currPos.X - position.X - 1;
		applyColors();
		if (isprint(currCharacter)) {
			if (!GetKeyState(VK_CAPITAL)) {
				currCharacter = tolower(currCharacter);
			}
			text.insert(indexToDelete, std::string( 1, char(currCharacter)) );
			setText(text);
			ctrl.setPosition({ currPos.X,currPos.Y });
			//std::cout << char(currCharacter);
		}
	}
}

void TextBox::deleteChar(COORD currPos) const {
	if (currPos.X > position.X + 1) {
		CCTRL.setPosition({ currPos.X - 1, currPos.Y });
		std::cout << " ";
	}
	CCTRL.setPosition({ currPos.X - 1, currPos.Y });
}

void TextBox::onFocus() {
	auto ctrl = CCTRL;
	this->setFocus(true);
	ctrl.setPosition({position.X + 1, position.Y + 1});
	ctrl.setCursorVisible(true);
}

void TextBox::onBlur() {
	auto ctrl = CCTRL;
	this->setFocus(false);
	CCTRL.setCursorVisible(false); //re-enbaled
}

void TextBox::setText(std::string _text) {
	text = _text;
	if (text.length() > width * height) text = text.substr(0, width * height);
	if (text.length() > maxSize) text = text.substr(0, maxSize);
	this->draw();
}

void TextBox::draw() {
	applyColors();
	UIComponent::draw();
	ConsoleController ctrl = CCTRL;
	// clear background
	//short text_len = static_cast<short>(text.length());
	ctrl.setPosition({ position.X + 1, position.Y + 1 });
	//GFX.moveTo(c.X, c.Y);
	for (short i = 0; i < height; i++) {
		for (short j = 0; j < width; j++) {
			std::cout << " ";
		}
		ctrl.setPosition({ position.X + 1, position.Y + i + 1 });
	}
	ctrl.setPosition({ position.X + 1, position.Y + 1 });


	std::stringstream ss(text);
	std::istream_iterator<std::string> begin(ss);
	std::istream_iterator<std::string> end;
	std::vector<std::string> vstrings(begin, end);
	text.clear();

	for (auto word : vstrings) {
		auto currPos = ctrl.getPosition();
		if (position.Y + height == currPos.Y + 1 &&
			currPos.X + word.length() + 1 > position.X + width) {
			break;
		}

		if (currPos.X + word.length() + 1 > position.X + width ) {
			ctrl.setPosition({ position.X + 1, currPos.Y + 1 });
			for (int i = 0; i <= position.X + width - currPos.X; i++)
				text.push_back(' ');
		}
		std::cout << word;
		text.append(word);
		lastIndexPosition = ctrl.getPosition();
		std::cout << " ";
		text.push_back(' ');
	}/*
	this->invertColors();
	std:: cout*/

	postDraw();
}