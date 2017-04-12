#include "Component.h"

Component::Component(short x_pos, short y_pos, int w, int h, BorderType border, Color tColor, Color bColor) :
	position { x_pos, y_pos }, width(w), height(h), borderType(border),
	textColor(tColor), backgroundColor(bColor) {
}