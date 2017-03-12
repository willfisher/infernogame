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
	GameplayScene gameplayScene(rand(), 0, &playerTexture);
	std::vector<Scene*> scenes = { &menuScene, &gameplayScene };
	SceneManager manager(scenes);

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();

		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				break;
			}
		}
		
		manager.Update(deltaTime);
		manager.Draw(window);

		window.display();
	}

	return 0;
}