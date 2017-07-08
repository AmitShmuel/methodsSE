#pragma once
#include "Graphics.h"
#include <vector>

using namespace std;

class Control
{

protected:
	short top, left;
	short width, height;
	
public:
	Control();
	Control(short left, short top, short width, short height);
	static Control* getFocus() { return NULL; };
	static void setFocus(Control& control) {};
	
	virtual void draw() = 0;
	virtual void mousePressed(int x, int y, bool isLeft) {};
	virtual void keyDown(int keyCode, char charecter) {};
	virtual short getLeft() { return 0; };
	virtual short getTop() { return 0; };
	virtual void setPosition(short top, short left) { this->left = left; this->top = top; };
	virtual void setSize(short width, short height) { this->width = width; this->height = height; };
	virtual void setWidth(int _width) { width = _width; };
	virtual void setHeight(int _height) { height = _height; };
	virtual void getAllControls(vector<Control*>* controls) {};
	virtual bool canGetFocus() { return FALSE; };
	~Control();
};

