#pragma once
#include <SFML\Graphics.hpp>
#include <string>

class Cloud
{
public:
	Cloud(sf::Texture* texture, sf::Vector2f& size, sf::Vector2f offset, float speed);
	~Cloud();

	void setPosition(sf::Vector2f position) { cloud1.setPosition(position + offset); cloud2.setPosition(position + offset); }

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

private:
	float speed;

	sf::Texture texture;
	sf::RectangleShape cloud1;
	sf::RectangleShape cloud2;

	sf::Vector2f offset;

	bool cloudOneInFront = true;
};

