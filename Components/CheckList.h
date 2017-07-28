#pragma once
#include "UIComponent.h"
#include <vector>
#include <string>
using namespace std;

typedef enum {Up, Down} Direction;

class CheckList : public UIComponent {

	struct Item {
		string text;
		bool checked;
	};

	vector<Item> list;
	short current;
	bool drawn, mouseEvent;

public:

	CheckList(string* options, int len, short pos_x, short pos_y, short width, BorderType border = Double, Color tColor = White, Color bColor = Black, UIComponent* parent = NULL);

	void draw();
	void mouseClicked(MOUSE_EVENT_RECORD);
	void keyPressed(KEY_EVENT_RECORD);
	void drawLine(Item item);
	void traverse(Direction d);

	bool isTraversable() override { return true; }
	bool isAtEnd() override { return list.size() - 1 == current; };
	void onFocus() override;
	void onBlur()  override;

	bool checkItem(bool toCheck, int index);
	bool canGetFocus() { return true; }
	const vector<string> getCheckedList() const;

	void setHeight(int _height) {}
	~CheckList() { CCTRL.detachObserver(this); }
};