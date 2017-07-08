#pragma once

#include <string>
#include <iostream>
#include <Windows.h>

#define GFX Graphics::init()
#define GFX_DESTROY Graphics::destroy()

using namespace std;

typedef enum Color { Black = 0x0000, Blue = 0x0001, Green = 0x0002, Red = 0x0004, Cyan = 0x0003, Purple = 0x0005, Orange = 0x0006, White = 0x0007
					, BrightBlue = 0x0009, BrightGreen = 0x000A, BrightRed = 0x000B, BrightCyan = 0x000C, BrightPurple = 0x000D, BrightOrange = 0x000E, BrightWhite = 0x000F
					} Color;
//typedef enum Color {Black, Blue, Green, Cyan, Red, Magenta, Brown, Lightgray, Darkgray, Lightblue,
//					Lightgreen, Lightcyan, Lightred, Lightmagenta, Yellow, White} Color;
typedef enum BorderType { None, Dotted, Solid, Double } BorderType;

struct BorderCharacters {
	char leftTopCorner, rightTopCorner, leftBottomCorner, rightBottomCorner, horizontal, vertical;
};

class Graphics
{
public:
	static Graphics& init(DWORD stdHandle = STD_OUTPUT_HANDLE);
	static void destroy();
	
	void clearScreen();
	void moveTo(int x, int y);
	void setBackground(Color color);
	void setForeground(Color color);
	void write(string s);
	void write(int x, int y, string s);
	void write(wstring s);
	void write(int x);
	void write(int x, int y, wstring s);
	void setCursorVisibility(bool isVisible);
private:
	static Graphics *instance;

	HANDLE _console;
	Color _background, _foreground;

	Graphics(DWORD stdHandle = STD_OUTPUT_HANDLE);
	Graphics(Graphics &g);
	void updateConsoleAttributes();
};

bool isInside(int x, int y, int left, int top, int width, int height);