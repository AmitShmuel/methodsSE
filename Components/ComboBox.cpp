#include "ComboBox.h"



ComboBox::ComboBox(vector<string>* options, short pos_x, short pos_y, short width, short height) : UIComponent(pos_x, pos_y, width, height) ,options(options) {
	this->selected = &options->front();
}


ComboBox::~ComboBox() {
	if (this->options) delete this->options;
}
