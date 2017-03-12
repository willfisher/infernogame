#include "Cloud.h"


Cloud::Cloud(sf::Texture* texture, sf::Vector2f& size, sf::Vector2f offset, float speed)
{
	this->speed = speed;
	cloud1.setSize(size);
	cloud2.setSize(size);
	cloud1.setTexture(texture);
	cloud2.setTexture(texture);
	cloud2.setOrigin(sf::Vector2f(-cloud1.getSize().x, 0));
	cloud1.setPosition(offset);
	cloud2.setPosition(offset);
	this->offset = offset;
}

Cloud::~Cloud()
{
}

void Cloud::Update(float deltaTime)
{

	cloud1.setOrigin(cloud1.getOrigin() + deltaTime * sf::Vector2f(speed, 0));
	cloud2.setOrigin(cloud1.getOrigin() - sf::Vector2f((cloudOneInFront ? 1.0 : -1.0) * cloud1.getSize().x, 0));
	if (cloudOneInFront)
	{
		if (cloud1.getOrigin().x > cloud1.getSize().x)
		{
			cloudOneInFront = false;
			cloud1.setOrigin(cloud2.getOrigin() - sf::Vector2f(cloud2.getSize().x, 0));
		}
	}
	else
	{
		if (cloud2.getOrigin().x > cloud2.getSize().x)
		{
			cloudOneInFront = true;
			cloud2.setOrigin(cloud1.getOrigin() - sf::Vector2f(cloud1.getSize().x, 0));
		}
	}
}

void Cloud::Draw(sf::RenderWindow & window)
{
	window.draw(cloud1);
	window.draw(cloud2);
}
