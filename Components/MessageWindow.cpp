#include "MessageWindow.h"


MessageWindow::MessageWindow(std::string _text, short x_pos, short y_pos, short w, short h,
	BorderType border, Color tColor, Color bColor, UIComponent *parent) 
	: UIComponent(x_pos, y_pos, w, h, border, tColor, bColor), text(_text),
	okBtn(NULL, "OK", x_pos + w/6, y_pos + h - 3, w / 6, 2, Solid, Orange, Blue),
	cancelBtn(NULL, "Cancel", x_pos + w -w/3, y_pos + h - 3, w / 6, 2, Solid, Orange, Blue) {

}

void MessageWindow::draw() {

	UIComponent::draw();

	COORD c = { left + 1, top + 1 };
	short text_len = static_cast<short>(text.length());
	GFX.moveTo(c.X, c.Y);
	for (short i = 0; i < width; i++) 
		std::cout << " ";

	// print centered text
	c = { left + 1 + ((width) / 2) - text_len / 2, top + 1 };
	GFX.moveTo(c.X, c.Y);
	std::cout << text;

	okBtn.draw();
	cancelBtn.draw();

	//listen();
}

bool MessageWindow::listen() {

	// TODO: button press

	for (;;) {
		//if(okBtn pressed) return true;
		//if(cancelBtn pressed) return false;
	}
}