#pragma once
#include "UIComponent.h"
#include <vector>
#include <string>
using namespace std;

class ComboBox : public UIComponent {
	vector<string>* options;
	string* selected;
public:
	ComboBox(vector<string>* options, short pos_x, short pos_y, short width, short height);
	bool canGetFocus() { return true; }
	~ComboBox();
};

