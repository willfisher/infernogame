#include "Player.h"



Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;

	player.setSize(sf::Vector2f(16 * GAME_SCALE, 32 * GAME_SCALE));
	collider.setSize(sf::Vector2f(8 * GAME_SCALE, 4 * GAME_SCALE));
	player.setTexture(texture);
}

Player::~Player()
{
}

void Player::Update(float deltaTime, CircleTerrain& terrain)
{
	sf::Vector2f movement(0.0f, 0.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		currentState = WalkLeftRight;
		currentIdleState = IdleRightLeft;
		movement.x -= speed * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		currentState = WalkLeftRight;
		currentIdleState = IdleRightLeft;
		movement.x += speed * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		currentState = WalkUp;
		currentIdleState = IdleUp;
		movement.y -= speed * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		currentState = WalkDown;
		currentIdleState = IdleDown;
		movement.y += speed * deltaTime;
	}

	if(movement.x != 0.0f)
		facingRight = movement.x > 0.0f;

	if (movement.x == 0.0f && movement.y == 0.0f)
		currentState = Idle;
	if(currentState != Idle || currentIdleState == IdleRightLeft)
		animation.Update(currentState, deltaTime, facingRight);
	else
		animation.Update(currentIdleState, deltaTime, false);
	player.setTextureRect(animation.uvRect);
	player.move(movement);
	sf::RectangleShape oldPos(collider);
	collider.setPosition(player.getPosition().x + (player.getSize().x - collider.getSize().x)/2.0f, player.getPosition().y + player.getSize().y - collider.getSize().y);
	
	terrain.BoundToMap(oldPos, getCollider());
	player.setPosition(collider.getPosition().x - (player.getSize().x - collider.getSize().x) / 2.0f, collider.getPosition().y + collider.getSize().y - player.getSize().y);
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(player);
}
