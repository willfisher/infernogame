#pragma once
#include <SFML\Graphics.hpp>
#include "Collider.h"
#include "Tile.h"
#include "ItemManager.h"
#include <string>

class CircleTerrain
{
public:
	CircleTerrain(int seed, int circleNum, sf::Vector2u dimensions, GameplayScene* scene);
	~CircleTerrain();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

	Tile::TileType getTileType(sf::Vector2u coordinates) { return map[coordinates.y * dimensions.x + coordinates.x].type; }
	sf::Vector2u getDimensions() { return dimensions; }
	sf::Vector2f getCoord(sf::Vector2u coordinates);

	void BoundToMap(sf::RectangleShape oldState, Collider& currentState);

private:
	int seed;
	int circleNum;

	void GenerateMap(GameplayScene* scene);
	sf::Vector2u GetNewPos(sf::Vector2u& currentPos, int tileDir);

	sf::Texture groundTexture;
	sf::Texture floatTexture;

	sf::Vector2u dimensions;
	std::vector<Tile> map;

	ItemManager itemManager;

	sf::RectangleShape parallax;
	static sf::Texture parallaxTexture;
};

