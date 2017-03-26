#include "CharacterManager.h"


CharacterManager::CharacterManager()
{
	std::ifstream characterFile("Saves/characters.txt");
	int cNum, cSeed, x, y;
	while (characterFile >> cNum >> cSeed >> x >> y)
		characters.push_back(Character(cNum, cSeed, sf::Vector2u(x, y)));
}


CharacterManager::~CharacterManager()
{
}

void CharacterManager::DeleteCurrentCharacter()
{
	characters.erase(characters.begin() + currentCharacter);
	if(currentCharacter != 0)
		currentCharacter--;
	WriteSave();
}

void CharacterManager::AddCharacter(int circleNumber, int circleSeed, sf::Vector2u & location)
{
	AddCharacter(Character(circleNumber, circleSeed, location));
}

void CharacterManager::AddCharacter(Character & character)
{
	characters.push_back(character);
	WriteSave();
}

void CharacterManager::ModifyCurrentCharacter(Character & newCharacter)
{
	characters.at(currentCharacter) = newCharacter;
	WriteSave();
}

void CharacterManager::WriteSave()
{
	std::ofstream characterFile;
	characterFile.open("Saves/characters.txt", std::ofstream::out | std::ofstream::trunc);
	characterFile.close();
	characterFile.open("Saves/characters.txt", std::ios_base::app | std::ios_base::out);
	if (characterFile.is_open())
	{
		characterFile.clear();
		for (int i = 0; i < characters.size(); i++)
		{
			if (i != 0)
				characterFile << "\n";
			characterFile << characters.at(i).toString();
		}
		characterFile.close();
	}
}

Character::Character(int circleNumber, int circleSeed, sf::Vector2u location)
{
	this->circleNumber = circleNumber;
	this->circleSeed = circleSeed;
	this->location = location;
}

Character::~Character()
{
}

std::string Character::toString()
{
	return "" + std::to_string(circleNumber) + " " + std::to_string(circleSeed) + " " + std::to_string(location.x) + " " + std::to_string(location.y);
}
