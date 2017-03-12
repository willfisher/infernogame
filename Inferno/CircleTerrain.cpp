#include "CircleTerrain.h"

static const sf::IntRect interiorRect(sf::Vector2i(0, 0), sf::Vector2i(16, 16));
static const sf::IntRect edgeRect(sf::Vector2i(16, 0), sf::Vector2i(16, 16));

sf::Texture CircleTerrain::parallaxTexture;

CircleTerrain::CircleTerrain(int seed, int circleNum, sf::Vector2u dimensions, GameplayScene* scene) :
	itemManager(seed)
{
	this->seed = seed;
	this->circleNum = circleNum;
	this->dimensions = dimensions;
	srand(abs(seed - circleNum));
	groundTexture.loadFromFile("Resources/Environment/Ground.png");
	floatTexture.loadFromFile("Resources/Environment/FloatGround.png");
	Tile::groundTexture = groundTexture;
	Tile::floatTexture = floatTexture;
	map.resize(dimensions.x * dimensions.y, Tile(Tile::Empty, seed, circleNum, sf::Vector2f(0, 0)));
	GenerateMap(scene);

	parallax.setPosition(sf::Vector2f(-16, -16));
	parallax.setSize(sf::Vector2f(300, 300));
	parallaxTexture.loadFromFile("Resources/Environment/Parallax.png");
	parallax.setTexture(&parallaxTexture);
}


CircleTerrain::~CircleTerrain()
{
}

void CircleTerrain::Update(float deltaTime)
{
	itemManager.Update(deltaTime);
}

void CircleTerrain::Draw(sf::RenderWindow & window)
{
	window.draw(parallax);
	for (Tile t : map)
		t.Draw(window);

	itemManager.Draw(window);
}

sf::Vector2f CircleTerrain::getCoord(sf::Vector2u coordinates)
{
	//return map[coordinates.y * dimensions.x + coordinates.x].getPosition();
	return sf::Vector2f(16 * coordinates.x, 16 * coordinates.y);
}

void CircleTerrain::BoundToMap(sf::RectangleShape oldState, Collider & currentState)
{
	sf::Vector2u currentTile(int(oldState.getPosition().x + oldState.getSize().x / 2.0f) / 16, int(oldState.getPosition().y + oldState.getSize().y / 2.0f) / 16);

	sf::RectangleShape collisionCheck(sf::Vector2f(16, 16));

	if (currentTile.x != 0 && getTileType(sf::Vector2u(currentTile.x - 1, currentTile.y)) == Tile::Empty)
	{
		collisionCheck.setPosition(getCoord(sf::Vector2u(currentTile.x - 1, currentTile.y)));
		currentState.CheckCollision(Collider(collisionCheck), 1.0f);
	}
	if (currentTile.x != getDimensions().x - 1 && getTileType(sf::Vector2u(currentTile.x + 1, currentTile.y)) == Tile::Empty)
	{
		collisionCheck.setPosition(getCoord(sf::Vector2u(currentTile.x + 1, currentTile.y)));
		currentState.CheckCollision(Collider(collisionCheck), 1.0f);
	}
	if (currentTile.y != 0 && getTileType(sf::Vector2u(currentTile.x, currentTile.y - 1)) == Tile::Empty)
	{
		collisionCheck.setPosition(getCoord(sf::Vector2u(currentTile.x, currentTile.y - 1)));
		currentState.CheckCollision(Collider(collisionCheck), 1.0f);
	}
	if (currentTile.y != getDimensions().y - 1 && getTileType(sf::Vector2u(currentTile.x, currentTile.y + 1)) == Tile::Empty)
	{
		collisionCheck.setPosition(getCoord(sf::Vector2u(currentTile.x, currentTile.y + 1)));
		currentState.CheckCollision(Collider(collisionCheck), 1.0f);
	}
	if (currentState.getPosition().x < 0)
		currentState.setPosition(sf::Vector2f(0, currentState.getPosition().y));
	else if (currentState.getPosition().x + currentState.getSize().x > dimensions.x * 16)
		currentState.setPosition(sf::Vector2f(dimensions.x * 16 - currentState.getSize().x, currentState.getPosition().y));
	if (currentState.getPosition().y < 0)
		currentState.setPosition(sf::Vector2f(currentState.getPosition().x, 0));
	else if (currentState.getPosition().y + currentState.getSize().y > dimensions.y * 16)
		currentState.setPosition(sf::Vector2f(currentState.getPosition().x, dimensions.y * 16 - currentState.getSize().y));

	itemManager.CheckCollisions(currentState);

	parallax.move((currentState.getPosition() - oldState.getPosition()) / 2.0f);
}

void CircleTerrain::GenerateMap(GameplayScene* scene)
{
	sf::Vector2u currentPos(0, 0);
	int tileCount = 0;

	while (tileCount < dimensions.x*dimensions.y / 2)
	{
		map[currentPos.y * dimensions.x + currentPos.x].setType(Tile::Interior);
		map[currentPos.y * dimensions.x + currentPos.x].setPosition(sf::Vector2f(16 * currentPos.x, 16 * currentPos.y));
		int tileDir = rand() % 4;
		currentPos = GetNewPos(currentPos, tileDir);
		tileCount++;
	}

	for (int y = 0; y < dimensions.y; y++)
	{
		for (int x = 0; x < dimensions.x; x++)
		{
			if (map[y * dimensions.x + x].type == Tile::Empty)
				continue;
			bool edge = false;
			bool floatEdge = false;
			int i = 3;
			switch (i)
			{
			case 3:
				if (y == dimensions.y - 1 || map[(y + 1) * dimensions.x + x].type == Tile::Empty)
				{
					floatEdge = true;
					break;
				}
				i--;
			case 2:
				if (x == dimensions.x - 1 || map[y * dimensions.x + x + 1].type == Tile::Empty)
				{
					edge = true;
					break;
				}
				i--;
			case 1:
				if (y == 0 || map[(y - 1) * dimensions.x + x].type == Tile::Empty)
				{
					edge = true;
					break;
				}
				i--;
			case 0:
				if (x == 0 || map[y * dimensions.x + x - 1].type == Tile::Empty)
				{
					edge = true;
					break;
				}
				break;
			}
			if (floatEdge)
				map[y * dimensions.x + x].setType(Tile::FloatEdge);
			else if (edge)
				map[y * dimensions.x + x].setType(Tile::Edge);
			else
				itemManager.GenerateItems(sf::Vector2u(x, y));
		}
	}
	int startIndex = rand() % map.size();
	for (int i = 0; i < map.size(); i++)
	{
		if (map[(i + startIndex) % map.size()].type == Tile::Interior)
		{
			itemManager.setPortal(Portal(getCoord(sf::Vector2u(((i + startIndex) % map.size()) % dimensions.x, ((i + startIndex) % map.size()) / dimensions.x)) - sf::Vector2f(2, 60 - 16), scene));
		}
	}
}

sf::Vector2u CircleTerrain::GetNewPos(sf::Vector2u& currentPos, int tileDir)
{
	int origDir = tileDir;
	for (int i = 0; i <= 1; i++)
	{
		switch (tileDir)
		{
		case 0:
			if (currentPos.x != 0 && map[currentPos.y * dimensions.x + currentPos.x - 1].type != Tile::Interior)
				return sf::Vector2u(currentPos.x - 1, currentPos.y);
			else
			{
				if ((origDir + 3) % 4 != tileDir)
					tileDir++;
				else
					goto repeat;
			}
		case 1:
			if (currentPos.y != dimensions.y - 1 && map[(currentPos.y + 1) * dimensions.x + currentPos.x].type != Tile::Interior)
				return sf::Vector2u(currentPos.x, currentPos.y + 1);
			else
			{
				if ((origDir + 3) % 4 != tileDir)
					tileDir++;
				else
					goto repeat;
			}
		case 2:
			if (currentPos.x != dimensions.x - 1 && map[currentPos.y * dimensions.x + currentPos.x + 1].type != Tile::Interior)
				return sf::Vector2u(currentPos.x + 1, currentPos.y);
			else
			{
				if ((origDir + 3) % 4 != tileDir)
					tileDir++;
				else
					goto repeat;
			}
		case 3:
			if (currentPos.y != 0 && map[(currentPos.y - 1) * dimensions.x + currentPos.x].type != Tile::Interior)
				return sf::Vector2u(currentPos.x, currentPos.y - 1);
			else
			{
				if ((origDir + 3) % 4 != tileDir)
					tileDir++;
				else
					goto repeat;
			}
			break;
		}
	}

repeat:
	int startIndex = rand() % map.size();
	for (int i = 0; i < map.size(); i++)
	{
		if (map[(startIndex + i) % map.size()].type == Tile::Interior)
		{
			return GetNewPos(sf::Vector2u(((startIndex + i) % map.size()) % dimensions.x, ((startIndex + i) % map.size())/dimensions.x), rand() % 4);
			break;
		}
	}
}
