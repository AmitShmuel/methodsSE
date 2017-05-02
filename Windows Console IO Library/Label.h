#pragma once
#include "UIComponent.h"
#include <string>

class Label: public UIComponent {
private:
	std::string text;

public:
	Label(std::string _text, short x_pos = 0, short y_pos = 0, int w = 0, int h = 0,
		BorderType border = NONE, Color tColor = BLACK, Color bColor = WHITE);
	
	void draw() override;
};
