#include "SceneManager.h"


int SceneManager::ACTIVE_SCENE = 0;

SceneManager::SceneManager(std::vector<Scene*> scenes)
{
	this->scenes = scenes;
}

SceneManager::~SceneManager()
{
}

void SceneManager::Draw(sf::RenderWindow & window)
{
	scenes[ACTIVE_SCENE]->Draw(window);
}

void SceneManager::Update(float deltaTime)
{
	scenes[ACTIVE_SCENE]->Update(deltaTime);
}
