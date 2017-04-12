#pragma once
#include "Component.h"
#include <string>

class Label: public Component {
private:
	std::string text;

	void drawBorder(COORD, BorderCharacters&) const;

public:
	Label(std::string _text, short x_pos = 0, short y_pos = 0, int w = 0, int h = 0,
		BorderType border = NONE, Color tColor = BLACK, Color bColor = WHITE);

	
	void draw() override;
	void removeFromScreen() override;
};
