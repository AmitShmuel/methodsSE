#include "Panel.h"
#include "DimensionException.h"


Panel::Panel(short pos_x, short pos_y, short width, short height, BorderType border, Color tColor, Color bColor, UIComponent* parent) : UIComponent(pos_x, pos_y, width, height, border, tColor, bColor, parent) {

}

void Panel::addComponent(UIComponent * component) {
	if (component->getHeight() + 2 > this->getHeight() || component->getWidth() + 2 + component->getXPosition() > this->getWidth())
		throw new DimentionException();

	if (component) {
		component->setParent(this);
		component->setPosition(this->getXPosition() + component->getXPosition() + 1, this->getYPosition() + component->getYPosition() + 1);
		this->components.push_back(component);
	}
}

void Panel::removeAll() {
	while (components.size() > 0) {
		delete components.back();
		components.pop_back();
	}
}

void Panel::draw() {
	UIComponent::draw();
	for (vector<UIComponent *>::iterator it = components.begin(); it != components.end(); ++it) {
		(*it)->draw();
	}
}


Panel::~Panel() {
	this->removeAll();
}
