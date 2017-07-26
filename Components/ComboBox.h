#pragma once
#include "UIComponent.h"
#include <vector>
#include <string>
using namespace std;

class ComboBox : public UIComponent {
	vector<string> options;
	int selected_index;
	bool open;
public:
	ComboBox(string* options, int len, short pos_x, short pos_y, short width, BorderType border = Double, Color tColor = White, Color bColor = Black, UIComponent* parent = NULL);

	void draw();

	// General UI Methods
	bool canGetFocus() { return true; }

	// ComboBox Specific
	void toggle();
	

	~ComboBox();
};

