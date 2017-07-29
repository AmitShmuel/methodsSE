#include "Panel.h"
#include "DimensionException.h"
#include <algorithm>

Panel::Panel(short pos_x, short pos_y, short width, short height, BorderType border, Color tColor, Color bColor, UIComponent* parent) : UIComponent(pos_x, pos_y, width, height, border, tColor, bColor, parent) {

}

void Panel::addComponent(UIComponent * component) {
	if (component->getHeight() + 2 > this->getHeight() || component->getWidth() + 2 + component->getXPosition() > this->getWidth())
		throw new DimentionException();

	if (component) {
		component->setParent(this);
		component->setPosition(this->getXPosition() + component->getXPosition() + 1, this->getYPosition() + component->getYPosition() + 1, true);
		this->components.push_back(component);
	}
}

void Panel::removeComponent(UIComponent * component) {
	std::vector<UIComponent*>::iterator position = std::find(this->components.begin(), this->components.end(), component);
	if (position != this->components.end()) {
		this->components.erase(position);
		delete component;
	}
}

void Panel::removeAll() {
	while (components.size() > 0) {
		delete components.back();
		components.pop_back();
	}
}

void Panel::draw() {
	applyColors();
	for (short i = 0; i < height + 1; ++i) {
		CCTRL.setPosition({ position.X, position.Y + i });
		for (short j = 0; j < width + 2; ++j) putchar(' ');
	}
	UIComponent::draw();
	for (vector<UIComponent *>::iterator it = components.begin(); it != components.end(); ++it) {
		(*it)->draw();
	}
	postDraw();
}


Panel::~Panel() {
	this->removeAll();
}
