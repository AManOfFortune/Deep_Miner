#pragma once

#include "Sorter.h"
#include "Deeper.h"
#include "Bomber.h"

class TitleScreen
{
public:
	//Constructor & Destructor
	TitleScreen();
	~TitleScreen();

	//Getter & Setter
	void setTitleOptions(int numOfOptions);
	void setTitleChoice(int choice);
	void setCharacterChoice(int choice);
	void setAllCharacters(std::vector<Miner*> allCharacters);
	int getTitleOptions();
	int getTitleChoice();
	int getCharacterChoice();
	std::vector<Miner*> getAllCharacters();

	//Functions
	void show();
	void initAllCharacters();
	Miner* chooseCharacter();

private:
	int _titleOptions;
	int _titleChoice;
	int _characterChoice;

	std::vector<Miner*> _allCharacters;
};