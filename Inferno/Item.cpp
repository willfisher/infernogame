#include "Item.h"
#include "Player.h"
#include "Scene.h"


sf::Texture Chest::chestTexture;
sf::Texture Coin::coinTexture;
Player* Item::player;
sf::Texture Portal::portalTexture;

Item::Item()
{
}


Item::~Item()
{
}

//---------------------------------------------------CHEST---------------------------------------------------------

Chest::Chest(sf::Vector2f position)
{
	chestTexture.loadFromFile("Resources/Props/Chest.png");
	chest.setPosition(position);
	chest.setTexture(&chestTexture);
	chest.setSize(sf::Vector2f(14, 14));
	chest.setTextureRect(sf::IntRect(0, 2, 14, 14));
	for (int i = 0; i < rand() % 4; i++)
	{
		sf::Vector2f pos(-6 - rand() % 10, rand() % 10);
		coins.push_back(Coin(position + pos));
	}
}

Chest::~Chest()
{
}

void Chest::Draw(sf::RenderWindow & window)
{
	window.draw(chest);
	if (open)
		for (Coin& coin : coins)
			coin.Draw(window);
}

void Chest::Update(float deltaTime)
{
}

void Chest::OnInteract()
{
	if (!open)
	{
		chest.setSize(sf::Vector2f(14, 16));
		chest.move(sf::Vector2f(0, -2));
		chest.setTextureRect(sf::IntRect(14, 0, 14, 16));
	}
	open = true;
}

void Chest::CheckCollide(Collider & collider)
{
	if (collider.CheckCollision(getCollider(), 1.0f))
		OnInteract();

	if (open)
		for (int i = coins.size() - 1; i >= 0; i--)
		{
			coins[i].CheckCollide(collider);
			if (coins[i].isConsumed())
				coins.erase(coins.begin() + i);
		}
}

//----------------------------------------------------COIN-------------------------------------------------------

Coin::Coin(sf::Vector2f& position) :
	coin(sf::Vector2f(6, 6))
{
	coinTexture.loadFromFile("Resources/Items/Coin.png");
	coin.setTexture(&coinTexture);
	coin.setPosition(position);
}

Coin::~Coin()
{
}

void Coin::Draw(sf::RenderWindow & window)
{
	window.draw(coin);
}

void Coin::Update(float deltaTime)
{
}

void Coin::OnInteract()
{
	Item::player->addCoins(1);
	consumed = true;
}

void Coin::CheckCollide(Collider & collider)
{
	if (collider.CheckCollision(getCollider(), 1.0f))
		OnInteract();
}

//-------------------------------------------------------PORTAL---------------------------------------------------------

Portal::Portal() :
	animation(&portalTexture, sf::Vector2u(3, 1), 0.15)
{
}

Portal::Portal(sf::Vector2f & position, GameplayScene* scene) :
	animation(&portalTexture, sf::Vector2u(3, 1), 0.15),
	portal(sf::Vector2f(20, 60))
{
	portalTexture.loadFromFile("Resources/Environment/Portal.png");
	portal.setTexture(&portalTexture);
	portal.setPosition(position);
	this->scene = scene;
}

Portal::~Portal()
{
}

void Portal::Draw(sf::RenderWindow & window)
{
	window.draw(portal);
}

void Portal::Update(float deltaTime)
{
	animation.Update(0, deltaTime, true);
	portal.setTextureRect(animation.uvRect);
}

void Portal::OnInteract()
{
	scene->NextCircle();
}

void Portal::CheckCollide(Collider & collider)
{
	if (collider.CheckCollision(Collider(portal), 1.0f))
		OnInteract();
}
