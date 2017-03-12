#pragma once
#include <functional>
#include <SFML\Graphics.hpp>
#include <string>

using namespace std;

class GUIButton
{
public:
	GUIButton(const function<void()>& on__Click, sf::Vector2f& position, sf::Vector2f& size, sf::Color stateColors[3], sf::Text text);
	~GUIButton();

	void onClick() { on_Click(); }
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

	void setPosition(sf::Vector2f& position);

private:
	enum ButtonState { UNACTIVE =  0, HIGHLIGHTED = 1, ACTIVE = 2 };
	ButtonState currentState;

	function<void()> on_Click;
	sf::Color stateColors[3];
	sf::RectangleShape button;

	void setState(sf::Vector2i& mousePos, sf::RenderWindow& window);

	sf::Text text;
};

