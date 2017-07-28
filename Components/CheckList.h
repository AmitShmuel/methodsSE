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
	short current;
	bool drawn;

public:

	CheckList(string* options, int len, short pos_x, short pos_y, short width, BorderType border = Double, Color tColor = White, Color bColor = Black, UIComponent* parent = NULL);

	void draw();
	void mouseClicked(MOUSE_EVENT_RECORD);
	void keyPressed(KEY_EVENT_RECORD);

	bool isTraversable() override { return true; }
	void onFocus() override;
	void onBlur()  override;

	bool checkItem(bool toCheck, int index);
	bool canGetFocus() { return true; }
	const vector<string> getCheckedList() const;


	~CheckList() { CCTRL.detachObserver(this); }
};