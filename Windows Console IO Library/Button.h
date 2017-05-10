#pragma once
#include "Label.h"

template < class ReturnType, class... Args >
class Button: public Label {
private:
	typedef ReturnType(*eventFunction)(Args...);
	eventFunction func;

public:
	Button(eventFunction funcPtr, std::string _text, short x_pos = 0, short y_pos = 0, int w =  0, int h = 0,
		   BorderType border = NONE, Color tColor = BLACK, Color bColor = WHITE, UIComponent* parent = NULL)
		: Label(_text, x_pos, y_pos, w, h, border, tColor, bColor, parent), func(funcPtr) {};

	// execute the evenFunction/.
	// @param: args : arguments to eventFunction
	ReturnType operator() (Args&... args) const {
		return (func)(args...);
	}

	~Button() { func = NULL; }
};