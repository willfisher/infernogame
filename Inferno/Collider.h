#pragma once
#include <SFML\Graphics.hpp>

class Collider
{
public:
	Collider(sf::RectangleShape& body);
	Collider(sf::RectangleShape& body, bool isTrigger);
	~Collider();

	void Move(float dx, float dy) { body.move(dx, dy); }

	bool CheckCollision(Collider& other, float resistance);
	sf::Vector2f getPosition() { return body.getPosition(); }
	void setPosition(sf::Vector2f newPos) { body.setPosition(newPos); }
	sf::Vector2f getHalfSize() { return body.getSize() / 2.0f; }
	sf::Vector2f getSize() { return body.getSize(); }
	sf::RectangleShape getBody() { return body; }

	bool isTrigger = false;

private:
	sf::RectangleShape& body;
};

