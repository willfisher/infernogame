#pragma once
#include <SFML\Graphics.hpp>
#include "Collider.h"
#include "Animation.h"
#include <memory>

class Player;
class GameplayScene;

class Item
{
public:
	Item();
	~Item();

	virtual void Draw(sf::RenderWindow& window) = 0;
	virtual void Update(float deltaTime) = 0;

	virtual void OnInteract() = 0;

	virtual void CheckCollide(Collider& collider) = 0;

	static void setPlayer(Player* player) { Item::player = player; }

	bool isConsumed() { return consumed; }

protected:
	static Player* player;
	bool consumed = false;
};

//-----------------------------------------------------------COIN------------------------------------------------------------------

class Coin : public Item
{
public:
	Coin(sf::Vector2f& position);
	~Coin();

	void Draw(sf::RenderWindow& window);
	void Update(float deltaTime);
	void OnInteract();

	void CheckCollide(Collider& collider);

	Collider getCollider() { return Collider(coin, true); }

	static sf::Texture coinTexture;

private:
	sf::RectangleShape coin;
};

//----------------------------------------------------------CHEST-------------------------------------------------------------------

class Chest : public Item
{
public:
	Chest(sf::Vector2f position);
	~Chest();

	static sf::Texture chestTexture;

	void Draw(sf::RenderWindow& window);
	void Update(float deltaTime);
	void OnInteract();

	void CheckCollide(Collider& collider);

	Collider getCollider() { return Collider(chest); }
	sf::Vector2f getPosition() { return chest.getPosition(); }
	void setPosition(sf::Vector2f position) { chest.setPosition(position); }
	bool isOpen() { return open; }

private:
	sf::RectangleShape chest;
	bool open = false;

	std::vector<Coin> coins;
};

//-----------------------------------------------------------PORTAL----------------------------------------------------------

class Portal : public Item
{
public:
	Portal();
	Portal(sf::Vector2f& position, GameplayScene* scene);
	~Portal();

	void Draw(sf::RenderWindow& window);
	void Update(float deltaTime);
	void OnInteract();

	void CheckCollide(Collider& collider);

private:
	static sf::Texture portalTexture;
	Animation animation;
	sf::RectangleShape portal;
	GameplayScene* scene;
};

