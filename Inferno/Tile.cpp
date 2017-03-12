#include "Tile.h"



sf::Texture Tile::groundTexture;
sf::Texture Tile::floatTexture;

Tile::Tile(TileType type, int seed, int circleNumber, sf::Vector2f position)
{
	this->type = type;
	this->seed = seed;
	this->circleNumber = circleNumber;
	tile.setSize(sf::Vector2f(16, type == FloatEdge ? 22 : 16));
	tile.setTextureRect(textureRect);
	setType(type);
	tile.setPosition(position);
}


Tile::~Tile()
{
}

void Tile::Draw(sf::RenderWindow & window)
{
	if (type == Empty)
		return;
	window.draw(tile);
}

void Tile::setType(TileType type)
{
	this->type = type;
	tile.setSize(sf::Vector2f(16, type == FloatEdge ? 22 : 16));
	switch (type)
	{
	case Interior:
		tile.setTexture(&groundTexture);
		textureRect.left = 0;
		textureRect.top = 0;
		textureRect.width = 16;
		textureRect.height = 16;
		break;
	case Edge:
		tile.setTexture(&groundTexture);
		textureRect.left = 16;
		textureRect.top = 0;
		textureRect.width = 16;
		textureRect.height = 16;
		break;
	case FloatEdge:
		tile.setTexture(&floatTexture);
		textureRect.left = 0;
		textureRect.top = 0;
		textureRect.width = 16;
		textureRect.height = 22;
		break;
	}
	tile.setTextureRect(textureRect);
}
