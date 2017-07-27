#pragma once
#include "UIComponent.h"
#include <vector>
#include <string>
using namespace std;


class CheckList : public UIComponent {

	struct Item {
		string text;
		bool checked;
	};

	vector<Item> list;

public:

	CheckList(string* options, int len, short pos_x, short pos_y, short width, BorderType border = Double, Color tColor = White, Color bColor = Black, UIComponent* parent = NULL);

	void draw();

	bool checkItem(int index);
	bool uncheckItem(int index);
	bool canGetFocus() { return true; }
	const vector<Item> getCheckedList() const;
};

