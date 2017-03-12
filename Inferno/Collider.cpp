#include "Collider.h"



Collider::Collider(sf::RectangleShape& body) :
	body(body)
{
}

Collider::Collider(sf::RectangleShape & body, bool isTrigger) :
	body(body)
{
	this->isTrigger = isTrigger;
}


Collider::~Collider()
{
}

bool Collider::CheckCollision(Collider & other, float resistance)
{
	sf::Vector2f otherHalfSize = other.getHalfSize();
	sf::Vector2f otherPosition = other.getPosition() + otherHalfSize;
	sf::Vector2f thisHalfSize = getHalfSize();
	sf::Vector2f thisPosition = getPosition() + thisHalfSize;

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;

	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		if (isTrigger || other.isTrigger)
			return true;

		resistance = std::min(std::max(resistance, 0.0f), 1.0f);

		if (abs(intersectX) < abs(intersectY))
		{
			if (deltaX > 0.0f)
			{
				Move(intersectX * resistance, 0.0f);
				other.Move(-intersectX * (1.0f - resistance), 0.0f);
			}
			else
			{
				Move(-intersectX * resistance, 0.0f);
				other.Move(intersectX * (1.0f - resistance), 0.0f);
			}
		}
		else
		{
			if (deltaY > 0.0f)
			{
				Move(0.0f, intersectY * resistance);
				other.Move(0.0f, -intersectY * (1.0f - resistance));
			}
			else
			{
				Move(0.0f, -intersectY * resistance);
				other.Move(0.0f, intersectY * (1.0f - resistance));
			}
		}

		return true;
	}

	return false;
}
