#include "ItemManager.h"



ItemManager::ItemManager(int seed)
{
	srand(seed);
}


ItemManager::~ItemManager()
{
}



void ItemManager::GenerateItems(sf::Vector2u& currentPos)
{
	if (rand() % 50 == 0)
		chests.push_back(Chest(sf::Vector2f(16 * currentPos.x + 1, 16 * currentPos.y - 4 - 2)));
}

void ItemManager::CheckCollisions(Collider & collider)
{
	for (Chest& chest : chests)
		chest.CheckCollide(collider);
	portal.CheckCollide(collider);
}

void ItemManager::Draw(sf::RenderWindow & window)
{
	for (Chest& chest : chests)
		chest.Draw(window);
	portal.Draw(window);
}

void ItemManager::Update(float deltaTime)
{
	portal.Update(deltaTime);
}
