#include <SFML\Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Scene.h"
#include "SceneManager.h"



int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 480), "Inferno");

	sf::Texture playerTexture;
	playerTexture.loadFromFile("Resources/Characters/Dante.png");

	float deltaTime = 0.0f;
	sf::Clock clock;

	srand(time(NULL));
	MenuScene menuScene;
	CharacterSelectionScene csScene;
	GameplayScene gameplayScene(rand(), 0, &playerTexture);
	std::vector<Scene*> scenes = { &menuScene, &csScene, &gameplayScene };
	SceneManager manager(scenes);

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		
		manager.Update(deltaTime);
		manager.Draw(window);

		window.display();
	}

	return 0;
}