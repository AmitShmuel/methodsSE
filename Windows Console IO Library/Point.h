#pragma once
#include <iostream>

class Point {
private:
	int x, y;

public:
	Point(int _x = 0,int _y = 0) : x(_x), y(_y) {};
	void setX(int _x) { x = _x; }
	void setY(int _y) { y = _y; }
	int getX() const { return x; }
	int getY() const { return y; }

	friend std::ostream& operator<<(std::ostream&, const Point&);
};