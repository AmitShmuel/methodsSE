#pragma once
#include "../Components/UIComponent.h"
class Border : public UIComponent {
	const UIComponent& component;
public:
	Border(const UIComponent& comp);
	~Border();
};

