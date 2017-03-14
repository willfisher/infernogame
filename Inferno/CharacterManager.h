#pragma once
#include <SFML\Graphics.hpp>
#include <fstream>

class Character
{
public:
	Character(int circleNumber, int circleSeed, sf::Vector2u location);
	~Character();

	int circleNumber;
	int circleSeed;
	sf::Vector2u location;

	std::string toString();
};

class CharacterManager
{
public:
	CharacterManager();
	~CharacterManager();

	int currentCharacter = 0;
	int characterCount() { return characters.size(); };
	Character& getCharacter() { return characters.at(currentCharacter); }
	Character& getCharacter(int i) { return characters.at(i); }
	std::vector<Character>& getCharacters() { return characters; };

	void DeleteCurrentCharacter();
	void AddCharacter(int circleNumber, int circleSeed, sf::Vector2u& location);
	void AddCharacter(Character& character);

private:
	std::vector<Character> characters;
};


