#include <iostream>
#include <Windows.h>
#include "TitleScreen.h"
#include "Config.h"

TitleScreen::TitleScreen()
{
    setTitleOptions(2);
    setTitleChoice(0);
    setAllCharacters(std::vector<Miner*>());
    initAllCharacters();
}

TitleScreen::~TitleScreen()
{
    while (_allCharacters.size() > 0) {
        _allCharacters.erase(_allCharacters.begin());
    }
}

void TitleScreen::setTitleOptions(int numOfOptions)
{
    _titleOptions = numOfOptions;
}

void TitleScreen::setTitleChoice(int choice)
{
    if (choice < 1)
        _titleChoice = 1;
    else if (choice > getTitleOptions())
        _titleChoice = getTitleOptions();
    else
        _titleChoice = choice;
}

void TitleScreen::setCharacterChoice(int choice)
{
    if (choice < 1)
        _characterChoice = 1;
    else if (choice > getAllCharacters().size())
        _characterChoice = static_cast<int>(getAllCharacters().size());
    else
        _characterChoice = choice;
}

void TitleScreen::setAllCharacters(std::vector<Miner*> allCharacters)
{
    _allCharacters = allCharacters;
}

int TitleScreen::getTitleOptions()
{
    return _titleOptions;
}

int TitleScreen::getTitleChoice()
{
    return _titleChoice;
}

int TitleScreen::getCharacterChoice()
{
    return _characterChoice;
}

std::vector<Miner*> TitleScreen::getAllCharacters()
{
    return _allCharacters;
}

void TitleScreen::show()
{
    setTitleChoice(1);
    
    //Necessary to remove any enter input before the title is displayed
    while (GetAsyncKeyState(VK_RETURN)) {};

    while (true) {
        system("cls");

        std::cout << "  _____                    __  __ _                 " << std::endl;
        std::cout << " |  __ \\                  |  \\/  (_)                " << std::endl;
        std::cout << " | |  | | ___  ___ _ __   | \\  / |_ _ __   ___ _ __ " << std::endl;
        std::cout << " | |  | |/ _ \\/ _ \\ '_ \\  | |\\/| | | '_ \\ / _ \\ '__|" << std::endl;
        std::cout << " | |__| |  __/  __/ |_) | | |  | | | | | |  __/ |   " << std::endl;
        std::cout << " |_____/ \\___|\\___| .__/  |_|  |_|_|_| |_|\\___|_|   " << std::endl;
        std::cout << "                  | |                               " << std::endl;
        std::cout << "                  |_|                               " << std::endl;

        if (getTitleChoice() == 1) {
            std::cout << "\033[;93m" << "\n\n  Play" << "\033[m" << std::endl;
            std::cout << "  Quit" << std::endl;
        }
        else if (getTitleChoice() == 2) {
            std::cout << "\n\n  Play" << std::endl;
            std::cout << "\033[;93m" << "  Quit" << "\033[m" << std::endl;
        }

        if (GetAsyncKeyState(VK_UP))
            setTitleChoice(getTitleChoice() - 1);
        else if (GetAsyncKeyState(VK_DOWN))
            setTitleChoice(getTitleChoice() + 1);
        else if (GetAsyncKeyState(VK_RETURN))
            break;
    }
}

void TitleScreen::initAllCharacters()
{
    _allCharacters.push_back(new Sorter(0, 0, false));
    _allCharacters.push_back(new Deeper(0, 0, false));
    _allCharacters.push_back(new Bomber(0, 0, false));
}

Miner* TitleScreen::chooseCharacter()
{
    setCharacterChoice(1);

    //Let player choose character
    while (true) {
        system("cls");

        std::cout << "Select your character:\n" << std::endl;

        for (int i = 0; i < getAllCharacters().size(); i++) {

            if(i + 1 == getCharacterChoice())
                std::cout << "\033[;93m" << getAllCharacters()[i]->getName() << " - " << getAllCharacters()[i]->getDescription() << "\033[m" << std::endl;
            else
                std::cout << getAllCharacters()[i]->getName() << " - " << getAllCharacters()[i]->getDescription() << std::endl;
        }

        if (GetAsyncKeyState(VK_UP))
            setCharacterChoice(getCharacterChoice() - 1);
        else if (GetAsyncKeyState(VK_DOWN))
            setCharacterChoice(getCharacterChoice() + 1);
        else if (GetAsyncKeyState(VK_RETURN))
            break;
    }

    //Select if character is player controlled
    bool playerControlledChoice = true;
    while (true) {
        system("cls");

        std::cout << "Player controlled?\n" << std::endl;

        if (playerControlledChoice) {
            std::cout << "\033[;93m" << "Yes" << "\033[m" << std::endl;
            std::cout << "No" << std::endl;
        }
        else {
            std::cout << "Yes" << std::endl;
            std::cout << "\033[;93m" << "No" << "\033[m" << std::endl;
        }

        if (GetAsyncKeyState(VK_UP))
            playerControlledChoice = true;
        else if (GetAsyncKeyState(VK_DOWN))
            playerControlledChoice = false;
        else if (GetAsyncKeyState(VK_RETURN))
            break;
    }

    getAllCharacters().at(getCharacterChoice() - 1)->setPlayerControlled(playerControlledChoice);

    //Randomize starting position
    getAllCharacters().at(getCharacterChoice() - 1)->setPosX(rand() % COLS);
    getAllCharacters().at(getCharacterChoice() - 1)->setPosY(rand() % ROWS);

    //Return a clone of the chosen character
    return getAllCharacters().at(getCharacterChoice() - 1)->clone();
}
