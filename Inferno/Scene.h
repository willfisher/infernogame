#pragma once
#include <SFML\Graphics.hpp>
#include "CircleTerrain.h"
#include "Player.h"
#include <string>
#include <functional>
#include "Dialogue.h"
#include "CloudSystem.h"
#include "GUIButton.h"
#include "CharacterManager.h"

using namespace std;

class Scene
{
public:
	static const unsigned VIEW_HEIGHT = 3 * 32 * 2; //192
	static const unsigned VIEW_WIDTH = 5 * 32 * 2; //320

	Scene();
	~Scene();

	virtual void Update(float deltaTime) = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;

	static sf::Font MAIN_FONT;

protected:
	void ResizeView(const sf::RenderWindow& window, sf::View& view);
	sf::Vector2u oldWindowSize;
};

//---------------------------------------------------------MENU SCENE-------------------------------------------------------

class MenuScene : public Scene
{
public:
	MenuScene();
	~MenuScene();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

private:
	sf::RectangleShape title;
	sf::Texture titleTexture;
	sf::View defaultView;

	sf::Text pressSpace;

	void SetUI();

	CloudSystem cloudSystem;
	sf::Texture cloudTexture1;
	sf::Texture cloudTexture2;
};

//--------------------------------------------CHARACTER SELECTION SCENE------------------------------------------------

class CharacterSelectionScene : public Scene
{
public:
	CharacterSelectionScene();
	~CharacterSelectionScene();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

	static CharacterManager characterManager;
	static void SetCharacter(int i);
	static void DeleteCharacter();
	static void NewCharacter();

private:
	sf::Text characterText;
	sf::Text characterDetails;

	void CreateButtons();
	std::vector<GUIButton> buttons;
	GUIButton newCharacter;
	GUIButton deleteCharacter;
};

//---------------------------------------------------GAMEPLAY SCENE----------------------------------------------------

class GameplayScene : public Scene
{
public:
	GameplayScene(int seed, int currentCircle, sf::Texture* texture);
	~GameplayScene();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

	void NextCircle();

private:
	int seed;
	int currentCircle = 0;
	CircleTerrain terrain;
	Player player;
	sf::View view;

	sf::RectangleShape background;
	static sf::Texture backgroundTexture;

	sf::Text circleText;
	sf::Text coinText;

	Dialogue introDialogue;

	int currentSin = 0;
	sf::Text sinText;

	sf::RectangleShape fadeOut;
	bool fading = false;
	bool goingIn = false;
	float scaleConst = 0;
};