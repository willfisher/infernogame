#pragma once
#include <SFML\Graphics.hpp>

class UIElement
{
public:
	virtual void Update(float deltaTime) = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;

	virtual void RegisterEvent(sf::Event evnt) = 0;
};

