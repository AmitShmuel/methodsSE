#pragma once
#include "UIComponent.h"
#include <vector>

using namespace std;

class Panel : public UIComponent {
	vector<UIComponent*> components;
public:
	Panel(short pos_x, short pos_y, short width, short height, BorderType border, Color tColor, Color bColor, UIComponent* parent);
	virtual void addComponent(UIComponent* component);
	virtual void removeComponent(UIComponent* component);
	virtual void removeAll();
	virtual void draw();
	~Panel();
};

