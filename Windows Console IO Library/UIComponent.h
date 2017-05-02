#pragma once
#include <Windows.h>
#include <stdio.h>

typedef enum BorderType {NONE, DOTTED, SOLID, DBL} BorderType;
typedef enum Color {BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY, DARKGRAY, LIGHTBLUE,
					LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE} Color;

struct BorderCharacters {
	char leftTopCorner, rightTopCorner, leftBottomCorner, rightBottomCorner, horizontal, vertical;
};

class UIComponent {

protected:
	UIComponent *parent;
	COORD position;
	int width, height;
	BorderType borderType;
	Color textColor, backgroundColor;

	//Windows STD handlersb & internal helpers
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hinput = GetStdHandle(STD_INPUT_HANDLE);

	//bool isVisible;
	void removeFromScreen() const;
	void drawBorder() const;

public:
	virtual ~UIComponent() = 0 {};
	UIComponent(short x_pos=0, short y_pos=0, int w=0, int h=0, BorderType border=NONE,
		Color tColor=BLACK, Color bColor=WHITE, UIComponent *parent = NULL);

	// Component functionality methods
	UIComponent& getRoot();
	virtual void addComponent(UIComponent& component) = 0 {};
	virtual void removeAll() = 0 {};
	virtual void draw() = 0;

	//Setters:
	//void setVisible(bool visible) { isVisible = visible; }
	void setBorderType(BorderType border) { borderType = border; draw(); }	//TODO
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