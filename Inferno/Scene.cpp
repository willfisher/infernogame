#include "Scene.h"
#include "SceneManager.h"
#include "Item.h"
#include "Dialogue.h"




sf::Font Scene::MAIN_FONT;
sf::Texture GameplayScene::backgroundTexture;

static const float FADE_OUT_TIME = 2.0f;
static const sf::Color FADE_COLOR = sf::Color::Red;

static const std::string sins[] = {"left turn on red",
"slowly raising chicken prices since 2008",
"stealing recycled metals",
"shoplifting three belts",
"selling a single crack stone"};

static const std::string introdialogue[] = { "Hey, welcome to Hell!",
"My name's Lucifer, and down here we place all of\nearth's good-for-nothin's into circles.",
"You might notice that what you're in lacks the crisp symmetry of\nyour typical circle and appears as a sporadic mess of tiles",
"...almost as if it has been randomly generated...",
"but don't mind that!\nSearch long enough and you'll find your way down to the next circle.",
"Ciao."};


Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

//----------------------------------------------MENU SCENE-----------------------------------------------------------------------

MenuScene::MenuScene() :
	title(sf::Vector2f(175, 50))
{
	titleTexture.loadFromFile("Resources/UI/Title.png");
	title.setTexture(&titleTexture);
	title.setOrigin(sf::Vector2f(title.getSize().x / 2.0f, 0));
	defaultView.setSize(sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT));
	defaultView.setCenter(defaultView.getSize() / 2.0f);

	MAIN_FONT.loadFromFile("Resources/UI/Fonts/forward.ttf");

	pressSpace.setFont(MAIN_FONT);
	pressSpace.setFillColor(sf::Color::Black);
	pressSpace.setCharacterSize(75);
	pressSpace.setScale(sf::Vector2f(0.1, 0.1));
	pressSpace.setString("PRESS SPACE TO CONTINUE");

	SetUI();

	cloudTexture1.loadFromFile("Resources/Environment/Clouds1.png");
	cloudSystem.addCloud(Cloud(&cloudTexture1, sf::Vector2f(320, 105), sf::Vector2f(0, 0), 50));
	cloudTexture2.loadFromFile("Resources/Environment/Clouds2.png");
	cloudSystem.addCloud(Cloud(&cloudTexture2, sf::Vector2f(320, 105), sf::Vector2f(0, 30), 100));
}

MenuScene::~MenuScene()
{
}

void MenuScene::Update(float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		SceneManager::ACTIVE_SCENE = 1;

	cloudSystem.Update(deltaTime);
}

void MenuScene::Draw(sf::RenderWindow & window)
{
	sf::Event evnt;
	while (window.pollEvent(evnt))
	{
		switch (evnt.type)
		{
		case sf::Event::Resized:
			ResizeView(window, defaultView);
			SetUI();
			break;
		}
	}

	window.clear(sf::Color::White);

	window.setView(defaultView);
	cloudSystem.setPosition(window.mapPixelToCoords(sf::Vector2i(0, 0)));
	cloudSystem.Draw(window);
	window.draw(title);
	window.draw(pressSpace);
}

void MenuScene::SetUI()
{
	defaultView.setCenter(defaultView.getSize() / 2.0f);
	title.setPosition(sf::Vector2f(defaultView.getSize().x / 2.0f, 25));
	pressSpace.setPosition(sf::Vector2f(defaultView.getSize().x / 2.0f - 133 / 2.0f, 25 + title.getPosition().y + title.getSize().y));
}

//--------------------------------------------CHARACTER SELECTION SCENE------------------------------------------------------------------

CharacterSelectionScene::CharacterSelectionScene()
{
}

CharacterSelectionScene::~CharacterSelectionScene()
{
}

//---------------------------------------------GAMEPLAY SCENE----------------------------------------------------------------------------

GameplayScene::GameplayScene(int seed, int currentCircle, sf::Texture* texture) :
	terrain(abs(seed - currentCircle), 0, sf::Vector2u(25, 25), this),
	view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT)),
	player(texture, sf::Vector2u(5, 6), 0.25f, 100.0f * GAME_SCALE),
	introDialogue(std::vector<std::string>(introdialogue, end(introdialogue)), &view, "Resources/UI/DevilPortrait.png", sf::RectangleShape(sf::Vector2f(50, 50)))
{
	this->seed = seed;
	this->currentCircle = currentCircle;

	oldWindowSize.x = VIEW_WIDTH;
	oldWindowSize.y = VIEW_HEIGHT;

	Item::setPlayer(&player);

	player.setPosition(sf::Vector2f(2, 2) - player.getSize());

	MAIN_FONT.loadFromFile("Resources/UI/Fonts/forward.ttf");

	coinText.setFont(MAIN_FONT);
	coinText.setFillColor(sf::Color::Black);
	coinText.setCharacterSize(50);
	coinText.setScale(sf::Vector2f(0.1, 0.1));
	circleText.setFont(MAIN_FONT);
	circleText.setCharacterSize(75);
	circleText.setScale(sf::Vector2f(0.1, 0.1));

	backgroundTexture.loadFromFile("Resources/Environment/Background.png");
	background.setTexture(&backgroundTexture);
	background.setSize(view.getSize());

	currentSin = rand() % size(sins);
	sinText.setString(sins[currentSin]);
	sinText.setFont(Scene::MAIN_FONT);
	sinText.setCharacterSize(75);
	sinText.setScale(sf::Vector2f(0.1, 0.1));

	fadeOut.setFillColor(sf::Color::Black);
}

GameplayScene::~GameplayScene()
{
}

void GameplayScene::Update(float deltaTime)
{
	if (!fading)
	{
		terrain.Update(deltaTime);
		player.Update(deltaTime, terrain);
	}
	else
	{
		scaleConst += (goingIn ? -1 : 1) * deltaTime / FADE_OUT_TIME;
		if (!goingIn && scaleConst >= 1)
		{
			scaleConst = 1;
			goingIn = true;
			currentCircle++;
			currentSin = rand() % size(sins);
			sinText.setString(sins[currentSin]);
			terrain = CircleTerrain(abs(seed - currentCircle), 0, sf::Vector2u(25, 25), this);
			player.setPosition(sf::Vector2f(2, 2) - player.getSize());
		}
		else if (goingIn && scaleConst <= 0)
		{
			fading = false;
		}
		fadeOut.setFillColor(sf::Color(FADE_COLOR.r * scaleConst, FADE_COLOR.g * scaleConst, FADE_COLOR.b * scaleConst));
	}
}

void GameplayScene::Draw(sf::RenderWindow & window)
{
	sf::Event evnt;
	while (window.pollEvent(evnt))
	{
		switch (evnt.type)
		{
		case sf::Event::Resized:
			ResizeView(window, view);
			background.setSize(view.getSize());
			break;
		}
	}

	view.setCenter(player.getPosition());

	window.setView(view);
	background.setPosition(window.mapPixelToCoords(sf::Vector2i(0, 0)));
	window.draw(background);
	terrain.Draw(window);
	player.Draw(window);

	circleText.setString("CIRCLE: " + std::to_string(currentCircle));
	circleText.setPosition(window.mapPixelToCoords(sf::Vector2i(0, 0)) + sf::Vector2f(4, 6));
	coinText.setString("GOLD: " + std::to_string(player.getCoins()));
	coinText.setPosition(circleText.getPosition() + sf::Vector2f(0, circleText.getGlobalBounds().height + 1));
	sf::FloatRect sinBounds = sinText.getGlobalBounds();
	sinText.setPosition(window.mapPixelToCoords(sf::Vector2i(window.getSize().x, 0)) - sf::Vector2f(sinBounds.width + 4, -6));

	window.draw(circleText);
	window.draw(coinText);
	window.draw(sinText);

	if (currentCircle == 0)
		introDialogue.Draw(window);

	if (fading)
	{
		fadeOut.setSize(view.getSize() * scaleConst);
		fadeOut.setOrigin(fadeOut.getSize() / 2.0f);
		fadeOut.setPosition(view.getCenter());
		window.draw(fadeOut);
	}
}

void GameplayScene::NextCircle()
{
	fading = true;
	goingIn = false;
	scaleConst = 0;
	fadeOut.setSize(sf::Vector2f(0, 0));
}
