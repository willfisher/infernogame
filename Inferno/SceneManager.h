#pragma once
#include "Scene.h"

class SceneManager
{
public:
	SceneManager(std::vector<Scene*> scenes);
	~SceneManager();

	static int ACTIVE_SCENE;

	static void setActiveScene(int id) { ACTIVE_SCENE = id; }
	void addScene(Scene* scene) { scenes.push_back(scene); }

	void Draw(sf::RenderWindow& window);
	void Update(float deltaTime);

private:
	std::vector<Scene*> scenes;
};

