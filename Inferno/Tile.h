#pragma once
#include <SFML\Graphics.hpp>

class Tile
{
public:
	enum TileType { Empty, Interior, Edge, FloatEdge };
	TileType type = Empty;

	static sf::Texture groundTexture;
	static sf::Texture floatTexture;

	Tile(TileType type, int seed, int circleNumber, sf::Vector2f position);
	~Tile();

	void Draw(sf::RenderWindow& window);

	void setType(TileType type);
	void setPosition(sf::Vector2f position) { tile.setPosition(position); }
	sf::Vector2f getPosition() { return tile.getPosition(); }

private:
	int seed;
	int circleNumber;
	sf::RectangleShape tile;

	sf::IntRect textureRect;
};

