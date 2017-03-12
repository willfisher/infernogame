#include "CloudSystem.h"



CloudSystem::CloudSystem()
{
}


CloudSystem::~CloudSystem()
{
}

void CloudSystem::setPosition(sf::Vector2f position)
{
	for (Cloud& cloud : clouds)
		cloud.setPosition(position);
}

void CloudSystem::Draw(sf::RenderWindow & window)
{
	for (Cloud& cloud : clouds)
		cloud.Draw(window);
}

void CloudSystem::Update(float deltaTime)
{
	for (Cloud& cloud : clouds)
		cloud.Update(deltaTime);
}
