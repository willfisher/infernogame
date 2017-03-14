#pragma once
#include <memory>
#include "UIElement.h"
#include <SFML\Graphics.hpp>

using namespace std;

class ScrollView
{
public:
	ScrollView();
	~ScrollView();

private:
	sf::FloatRect boundingBox;

	std::vector<std::shared_ptr<UIElement>> elements;
};

