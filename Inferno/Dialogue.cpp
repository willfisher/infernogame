#include "Dialogue.h"
#include "Scene.h"


static sf::Color boxColor = sf::Color::White;
static const sf::Color outlineColor = sf::Color::Red;

Dialogue::Dialogue(std::vector<std::string> textLines, sf::View* view,  std::string portraitTextureFile, sf::RectangleShape portrait)
{
	this->portrait = portrait;
	portraitTexture.loadFromFile(portraitTextureFile);
	this->portrait.setTexture(&portraitTexture);
	this->view = view;
	this->textLines = textLines;
	boxColor.a = 150;
	dialogueRect.setOutlineColor(outlineColor);
	dialogueRect.setFillColor(boxColor);
	dialogueRect.setOutlineThickness(1);
	currentText.setFont(Scene::MAIN_FONT);
	currentText.setCharacterSize(50);
	currentText.setScale(sf::Vector2f(0.1, 0.1));
	currentText.setString(textLines[currentIndex]);
	currentText.setFillColor(sf::Color::Black);
	SetSize();

	pressSpace.setFont(Scene::MAIN_FONT);
	pressSpace.setCharacterSize(50);
	pressSpace.setScale(sf::Vector2f(0.07, 0.07));
	pressSpace.setFillColor(sf::Color::Black);
	pressSpace.setString("PRESS SPACE");
}

Dialogue::~Dialogue()
{

}

void Dialogue::Draw(sf::RenderWindow & window)
{
	if (currentIndex >= textLines.size())
		return;

	sf::Event evnt;
	while (window.pollEvent(evnt))
	{
		switch (evnt.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::KeyPressed:
			if (evnt.key.code == sf::Keyboard::Space)
			{
				currentIndex++;
				if (currentIndex >= textLines.size())
					return;
				currentText.setString(textLines[currentIndex]);
			}
			break;
		}
	}

	SetSize();
	portrait.setPosition(window.mapPixelToCoords(sf::Vector2i(0, window.getSize().y)) - sf::Vector2f(0, portrait.getSize().y));
	dialogueRect.setPosition(window.mapPixelToCoords(sf::Vector2i(window.getSize().x / 2.0f, window.getSize().y)));
	currentText.setPosition(dialogueRect.getPosition() - dialogueRect.getOrigin() + sf::Vector2f(5 + portrait.getSize().x, 5));
	pressSpace.setPosition(window.mapPixelToCoords(sf::Vector2i(window.getSize().x, window.getSize().y)) - sf::Vector2f(5 + 30, 5 + 3));

	window.draw(dialogueRect);
	window.draw(currentText);
	window.draw(portrait);
	window.draw(pressSpace);
}

void Dialogue::SetSize()
{
	dialogueRect.setSize(sf::Vector2f((*view).getSize().x - 2, 39));
	dialogueRect.setOrigin(dialogueRect.getSize().x / 2.0f, 40);
}
