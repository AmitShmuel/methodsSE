#pragma once
#include "Label.h"

class MessageWindow : public UIComponent {

private:

	Label textAndFrame; // avoiding code reuse, label's draw does exactly what we need here.
	// Button okBtn, cancelBtn

public:
	MessageWindow::MessageWindow(std::string _text, short x_pos = 0, short y_pos = 0, short w = 0, short h = 0,
		BorderType border = Solid, Color tColor = Black, Color bColor = White)
		: UIComponent(x_pos, y_pos, w, h, border, tColor, bColor),
		textAndFrame(_text, x_pos, y_pos, w, h < 4 ? 4 : h, border == None ? Solid : border, tColor, bColor)/*,
		okBtn(),
		cancelBtn()*/ {}
	
	bool listen();

	void draw() override;
	void addComponent(UIComponent* component) {};
	void removeAll() {};
	~MessageWindow() {};
};