#pragma once
#include "UIComponent.h"
#include <string>

class Label: public UIComponent {
private:
	std::string text;

public:
	Label(std::string _text, short x_pos = 0, short y_pos = 0, short w = 0, short h = 0,
		BorderType border = None, Color tColor = Black, Color bColor = White, UIComponent *parent = NULL);
	
	void draw() override;
	void addComponent(UIComponent& component) {};
	void removeAll() {};
	~Label() {};
};
