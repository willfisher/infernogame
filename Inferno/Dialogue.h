#pragma once
#include <string>
#include <SFML\Graphics.hpp>

class Dialogue
{
public:
	Dialogue(std::vector<std::string> textLines, sf::View* view, std::string portraitTextureFile, sf::RectangleShape portrait);
	~Dialogue();

	void Draw(sf::RenderWindow& window);

private:
	sf::View* view;
	std::vector<std::string> textLines;
	sf::Text text;

	int currentIndex = 0;

	sf::RectangleShape dialogueRect;
	sf::RectangleShape portrait;
	sf::Texture portraitTexture;
	sf::Text currentText;

	sf::Text pressSpace;

	void SetSize();
};

