#pragma once
#include "UIComponent.h"
#include <vector>

using namespace std;

class Panel : public UIComponent {
	vector<UIComponent*> components;
public:
	Panel(short pos_x, short pos_y, short width, short height);
	virtual void addComponent(UIComponent* component);
	virtual void removeAll();
	virtual void draw();
	~Panel();
};

