#pragma once
#include <string>
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include "Collider.h"
#include "CircleTerrain.h"

using namespace std;

static const int GAME_SCALE = 1;

class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
	~Player();

	void Update(float deltaTime, CircleTerrain& terrain);
	void Draw(sf::RenderWindow& window);

	sf::Vector2f getSize() { return player.getSize(); }

	sf::Vector2f getPosition() { return player.getPosition();  }
	Collider getCollider() { return Collider(collider); }
	void setPosition(sf::Vector2f newPos) { player.setPosition(newPos); collider.setPosition(player.getPosition().x, player.getPosition().y + player.getSize().y - collider.getSize().y); }

	int getCoins() { return coins; }
	void addCoins(int amount) { coins += amount; }

private:
	float speed;

	sf::RectangleShape player;
	sf::RectangleShape collider;

	enum AnimState {Idle = 0, WalkLeftRight = 3, WalkUp = 5, WalkDown = 4};
	AnimState currentState = Idle;
	enum IdleState {IdleRightLeft = 0, IdleDown = 1, IdleUp = 2};
	IdleState currentIdleState = IdleRightLeft;

	Animation animation;

	bool facingRight = true;

	int coins = 0;
};

