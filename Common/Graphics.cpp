#include "Graphics.h"

Graphics *Graphics::instance = 0;

Graphics::Graphics(DWORD stdHandle)
	: _console(GetStdHandle(stdHandle)), _background(Color::Black), _foreground(Color::White)
{
	updateConsoleAttributes();
}

Graphics & Graphics::init(DWORD stdHandle)
{
	if (instance == NULL) {
		instance = new Graphics(stdHandle);
	}
	return *instance;
}

void Graphics::destroy()
{
	if (instance)
		delete instance;
}

void Graphics::clearScreen()
{
	DWORD d;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(_console, &csbi);
	auto size = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputAttribute(_console, csbi.wAttributes, size, { 0, 0 }, &d);
	FillConsoleOutputCharacter(_console, L' ', size, { 0, 0 }, &d);
}

void Graphics::moveTo(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(_console, c);
}

void Graphics::setBackground(Color color)
{
	_background = color;
	updateConsoleAttributes();
}

void Graphics::setForeground(Color color)
{
	_foreground = color;
	updateConsoleAttributes();
}

void Graphics::write(string s)
{
	WriteConsoleA(_console, s.c_str(), s.size(), nullptr, nullptr);
}

void Graphics::write(wstring s)
{
	WriteConsoleW(_console, s.c_str(), s.size(), nullptr, nullptr);
}

void Graphics::write(int x)
{
	cout << x;
}

void Graphics::write(int x, int y, string s)
{
	moveTo(x, y);
	write(s);
}

void Graphics::write(int x, int y, wstring s)
{
	moveTo(x, y);
	write(s);
}

void Graphics::setCursorVisibility(bool isVisible)
{
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(_console, &cci);
	cci.bVisible = isVisible;
	SetConsoleCursorInfo(_console, &cci);
}

void Graphics::updateConsoleAttributes()
{
	DWORD attributes = 0;
	attributes |= _foreground | 16 * _background;
	SetConsoleTextAttribute(_console, attributes);
}

bool isInside(int x, int y, int left, int top, int width, int height)
{
	x -= left;
	y -= top;
	return x >= 0 && y >= 0 && x < width && y < height;
}