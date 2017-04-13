﻿#pragma once
#include "Point.h"
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

typedef enum BorderType {NONE, DOTTED, SOLID} BorderType;
typedef enum Color {BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY, DARKGRAY, LIGHTBLUE,
					LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE} Color;

struct BorderCharacters {
	char leftTopCorner, rightTopCorner, leftBottomCorner, rightBottomCorner, horizontal, vertical;
};

class Component {

protected:
	BorderType borderType;
	int width, height;
	COORD position;
	Color textColor, backgroundColor;

	//Windows STD handlersb & internal helpers
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hinput = GetStdHandle(STD_INPUT_HANDLE);

	//bool isVisible;
	void removeFromScreen() const;
	virtual void draw() = 0;

	void drawBorder() const;

public:
	virtual ~Component() = 0 {};
	Component(short x_pos=0, short y_pos=0, int w=0, int h=0, BorderType border=NONE,
		Color tColor=BLACK, Color bColor=WHITE);

	//Setters:
	//void setVisible(bool visible) { isVisible = visible; }
	void setBorderType(BorderType border) { borderType = border; }	//TODO
	void setWidth(int _width) { width = _width;}					//TODO
	void setHeight(int _height) { height = _height;}				//TODO
	void setPosition(short _x, short _y) { removeFromScreen(); position = {_x, _y}; draw();}
	void setTextColor(Color color) { removeFromScreen();  textColor = color; draw(); }
	void setBackgroundColor(Color color) { removeFromScreen(); backgroundColor = color; draw(); }
	
	//Getters:
//	bool isVisible() const { return isVisible; }
	BorderType getBorderType() const { return borderType; }
	int getWidth() const { return width; }
	int getHeight() const { return height; }
	short getXPoisition() const { return position.X; }
	short getYPosition() const { return position.Y; }
	Color getTextColor() const { return textColor; }
	Color getBackgroundColor() const { return backgroundColor; }
};