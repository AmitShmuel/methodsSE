#pragma once
#include "UIComponent.h"
#include "IOConsoleException.h"

class NumericBox: public UIComponent {
private:
	int value, minimum, maximum;
	
	void drawValue() const;
	void drawOperators() const;

public:
	NumericBox(int _val=0, int _min=-INT_MIN, int _max=INT_MAX, short x_pos = 0, short y_pos = 0, int w = 0, int h = 0, BorderType border = NONE,
		Color tColor = BLACK, Color bColor = WHITE, UIComponent *parent = NULL);

	void draw() override;

	// TODO: remove it from here!
	void addComponent(UIComponent&) override {};
	void removeAll() override {};

	// setters
	void setValue(int);
	void setMin(int);
	void setMax(int);

	// getters
	int getValue() const { return value; }
	int getMin()   const { return minimum; }
	int getMax()   const { return maximum; }

	void increment();
	void decrement();
};
