#pragma once
#include "Item.h"
#include "Collider.h"

class ItemManager
{
public:
	ItemManager(int seed);
	~ItemManager();

	void GenerateItems(sf::Vector2u& currentPos);
	void CheckCollisions(Collider& collider);
	void Draw(sf::RenderWindow& window);
	void Update(float deltaTime);

	void setPortal(Portal portal) { this->portal = portal; };

private:
	std::vector<Chest> chests;
	Portal portal;
};

