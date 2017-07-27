#pragma once
#include "../Common/ConsoleController.h"
#include <iostream>

//typedef enum Color {
//	Black, Blue, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY, DARKGRAY, LIGHTBLUE,
//	LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE
//} Color;

struct BorderCharacters {
	char leftTopCorner, rightTopCorner, leftBottomCorner, rightBottomCorner, horizontal, vertical;
};

class UIComponent {

protected:
	UIComponent *parent;
	COORD position;
	short width, height;
	BorderType borderType;
	Color textColor, backgroundColor;
	bool focus;

	//bool isVisible;
	void removeFromScreen() const;
	void drawBorder() const;

public:
	virtual ~UIComponent() = 0 {};
	UIComponent(short x_pos = 0, short y_pos = 0, int w = 0, int h = 0, BorderType border = None,
		Color tColor = Black, Color bColor = White, UIComponent *parent = NULL);

	// Component functionality methods
	UIComponent& getRoot();
	virtual void addComponent(UIComponent& component) {};
	virtual void removeAll() {};
	virtual void draw() = 0;

	// General UI Methods
	virtual bool canGetFocus() { return false; }
	virtual void mouseClicked(MOUSE_EVENT_RECORD) {}
	virtual void keyPressed(KEY_EVENT_RECORD) {}
	virtual bool isTraversable() { return false; }
	virtual void setFocus(bool focus) { this->focus = focus; }
	virtual void postDraw() { CCTRL.restoreDefaultColors(); }
	void invertColors();
	void applyColors();

	// setters:
	//void setVisible(bool visible) { isVisible = visible; }
	void setBorderType(BorderType border) { borderType = border; draw(); }
	void setParent(UIComponent* p) { parent = p; }
	virtual void setWidth(int _width) { removeFromScreen(); width = _width; draw(); }
	virtual void setHeight(int _height) { removeFromScreen(); height = _height; draw(); }
	void setPosition(short _x, short _y) { removeFromScreen(); position = { _x, _y }; draw(); }
	void setTextColor(Color color) { textColor = color; draw(); }
	void setBackgroundColor(Color color) { backgroundColor = color; draw(); }

	// getters:
	//	bool isVisible() const { return isVisible; }
	BorderType getBorderType()		const { return borderType; }
	int		   getWidth()			const { return width; }
	int		   getHeight()			const { return height; }
	COORD      getDimentions()		const { return { width, height }; }
	COORD	   getPosition()		const { return position; }
	short	   getXPosition()		const { return position.X; }
	short	   getYPosition()		const { return position.Y; }
	Color	   getTextColor()		const { return textColor; }
	Color	   getBackgroundColor() const { return backgroundColor; }
	bool	   hasFocus() { return this->focus; }
};






/*==========================*/

//#pragma once
////#include "ConsoleController.h"
//#include "../Common/Control.h"
//#include "../Common/Graphics.h"
//#include <stdio.h>
//
////typedef enum BorderType {NONE, DOTTED, SOLID, DBL} BorderType;
////typedef enum UIColor {BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY, DARKGRAY, LIGHTBLUE,
////						LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE} UIColor;
//
//class UIComponent : public Control {
//
//protected:
//	UIComponent *parent;
//	BorderType borderType;
//	Color textColor, backgroundColor;
//
//	//bool isVisible;
//	void removeFromScreen() const;
//	void drawBorder() const;
//
//public:
//	virtual ~UIComponent() = 0 {};
//	UIComponent(short x_pos=0, short y_pos=0, short w=0, short h=0, BorderType border = None,
//		Color tColor=Black, Color bColor=White, UIComponent *parent = NULL);
//
//	// Component functionality methods
//	UIComponent& getRoot();
//	virtual void addComponent(UIComponent* component) = 0 {};
//	virtual void removeAll() = 0 {};
//	virtual void draw() = 0;
//
//	//Setters:
//	//void setVisible(bool visible) { isVisible = visible; }
//	void setBorderType(BorderType border) { borderType = border; draw(); }
//	void setPosition(short _x, short _y) { removeFromScreen(); left = _x; top = _y; draw(); }
//	void setTextColor(Color color, bool intensity = false) { removeFromScreen();  textColor = color; draw(); }
//	void setBackgroundColor(Color color, bool intensity = false) { removeFromScreen(); backgroundColor = color; draw(); }
//	
//	//Getters:
////	bool isVisible() const { return isVisible; }
//	BorderType getBorderType() const { return borderType; }
//	int getWidth() const { return width; }
//	int getHeight() const { return height; }
//	short getXPoisition() const { return left; }
//	short getYPosition() const { return top; }
//	Color getTextColor() const { return textColor; }
//	Color getBackgroundColor() const { return backgroundColor; }
//};