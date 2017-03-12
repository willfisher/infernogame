#pragma once
#include <SFML\Graphics.hpp>
#include "Cloud.h"

using namespace std;

class CloudSystem
{
public:
	CloudSystem();
	~CloudSystem();

	void addCloud(Cloud cloud) { clouds.push_back(cloud); }
	void setPosition(sf::Vector2f position);

	void Draw(sf::RenderWindow& window);
	void Update(float deltaTime);

private:
	std::vector<Cloud> clouds;
};

