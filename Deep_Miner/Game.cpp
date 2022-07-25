#include "Game.h"
#include <Windows.h>
#include <iostream>
#include "Config.h"

Game::Game()
{
	setMiners(std::vector<Miner*>());
}

void Game::setWorld(World* newWorld)
{
	_gameWorld = newWorld;
}

void Game::setMiners(std::vector<Miner*> miners)
{
	_miners = miners;
}

void Game::setCurrentMiner(int newMinerIndex)
{
	if (newMinerIndex >= getMiners().size())
		_currentMinerIndex = 0;
	else
		_currentMinerIndex = newMinerIndex;
}

World* Game::getWorld()
{
	return _gameWorld;
}

//One thing to note on this function:
//It returns a COPY of the miners vector, so if we want to do anything to the vector itself and not the miners,
//we need to refer to the actual variable _miners and cannot use getMiners()
std::vector<Miner*> Game::getMiners()
{
	return _miners;
}

int Game::getCurrentMinerIndex()
{
	return _currentMinerIndex;
}

void Game::start()
{
	TitleScreen gameTitleScreen;

	while (gameTitleScreen.getTitleChoice() != gameTitleScreen.getTitleOptions()) {

		gameTitleScreen.show();

		//If player chooses play
		if (gameTitleScreen.getTitleChoice() == 1)
		{
			//Initialize game variables
			setWorld(new World());
			setCurrentMiner(0);

			//Add two miners
			addMiner(gameTitleScreen.chooseCharacter());
			addMiner(gameTitleScreen.chooseCharacter());
			//Main game loop
			gameLoop();
			//Print the winner
			printWinner();

			//Free the world object
			delete getWorld();

			//Free the miner objects
			//We do not need to delete them because vectors to that automatically to all objects stored in them
			//As long as the miner vector is not size 0
			while (_miners.size() > 0) {
				//Erase the first position of the vector
				_miners.erase(_miners.begin());
			}
		}
	}
}

void Game::gameLoop()
{
	while (!worldEmpty()) {
		system("cls");
		//Renders world
		getWorld()->render(getMinerPositions());
		//Renders stats
		renderMinersStats();

		//If current miner is not playercontrolled, choose a random direction
		int randomDir = 0;
		if (!getMiners()[getCurrentMinerIndex()]->isPlayerControlled())
			randomDir = (rand() % 5) + 1;

		//Walk in specified direction if possible, then do round actions
		if (GetAsyncKeyState(VK_UP) || randomDir == 1) { //Up
			if (!getMiners()[getCurrentMinerIndex()]->moveUp()) continue;
			doRoundActions();
		}
		else if (GetAsyncKeyState(VK_DOWN) || randomDir == 2) { //Down
			if (!getMiners()[getCurrentMinerIndex()]->moveDown()) continue;
			doRoundActions();
		}
		else if (GetAsyncKeyState(VK_LEFT) || randomDir == 3) { //Left
			if (!getMiners()[getCurrentMinerIndex()]->moveLeft()) continue;
			doRoundActions();
		}
		else if (GetAsyncKeyState(VK_RIGHT) || randomDir == 4) { //Right
			if (!getMiners()[getCurrentMinerIndex()]->moveRight()) continue;
			doRoundActions();
		}
		else if (GetAsyncKeyState(VK_SHIFT) || randomDir == 5) { //Stay
			doRoundActions();
		}
		else if (GetAsyncKeyState(VK_ESCAPE)) { //Stop playing
			break;
		}
	}
}

void Game::doRoundActions()
{
	//Drill
	getMiners()[getCurrentMinerIndex()]->drill(getWorld());
	//Shuffle world if needed
	shuffleWorld();
	//Does all status effect actions
	doStatusEffectActions();
	//Sets the current to the next miner
	nextMiner();
}

void Game::doStatusEffectActions()
{
	//Decrease stun counter
	getMiners()[getCurrentMinerIndex()]->setStunCounter(getMiners()[getCurrentMinerIndex()]->getStunCounter() - 1);

	//If miner is getting teleported, find first lowest position and teleport him there
	if (getMiners()[getCurrentMinerIndex()]->getTeleportCounter() != 0) {
		int lowest = 10;
		int lowestPosX = 0;
		int lowestPosY = 0;

		for (int rowIndex = 0; rowIndex < ROWS; rowIndex++) {
			for (int colIndex = 0; colIndex < COLS; colIndex++) {
				//If the value at the given xy-position is greater than 0 and lower than the current lowest, save position & value
				if (getWorld()->getWorld()->at(rowIndex).at(colIndex).at(0) > 0 && getWorld()->getWorld()->at(rowIndex).at(colIndex).at(0) < lowest) {
					lowest = getWorld()->getWorld()->at(rowIndex).at(colIndex).at(0);
					lowestPosX = colIndex;
					lowestPosY = rowIndex;
				}
			}
		}

		//Print the updated world & message to inform the player of his impending teleport
		if (getMiners()[getCurrentMinerIndex()]->isPlayerControlled()) {
			system("cls");
			//Renders world
			getWorld()->render(getMinerPositions());
			//Renders stats
			renderMinersStats();

			std::cout << "\nYou're about to be teleported to (" << lowestPosX + 1 << "|" << lowestPosY + 1 << ")...\n" << std::endl;
			system("pause");
		}

		//Set miner to new position
		getMiners()[getCurrentMinerIndex()]->setPosX(lowestPosX);
		getMiners()[getCurrentMinerIndex()]->setPosY(lowestPosY);

		//Decrease teleport counter
		getMiners()[getCurrentMinerIndex()]->setTeleportCounter(getMiners()[getCurrentMinerIndex()]->getTeleportCounter() - 1);
	}
}

void Game::addMiner(Miner* miner)
{
	_miners.push_back(miner);
}

std::vector<std::vector<int>> Game::getMinerPositions()
{
	std::vector<std::vector<int>> positions;

	for (int i = 0; i < getMiners().size(); i++) {
		std::vector<int> position = {getMiners()[i]->getPosX(), getMiners()[i]->getPosY()};
		positions.push_back(position);
	}

	return positions;
}

void Game::nextMiner()
{
	setCurrentMiner(getCurrentMinerIndex() + 1);
}

void Game::renderMinersStats()
{
	for (int i = 0; i < getMiners().size(); i++) {
		std::cout << "\nMiner " << i + 1 << ": " << std::endl;
		std::cout << "Score [" << getMiners()[i]->getScore() << "]" << std::endl;

		if (getMiners()[i]->getStunCounter() != 0)
			std::cout << "Drill broken for [" << getMiners()[i]->getStunCounter() << "] rounds" << std::endl;

		if (getMiners()[i]->getTeleportCounter() != 0)
			std::cout << "About to be teleported [" << getMiners()[i]->getTeleportCounter() << "] times" << std::endl;
	}
}

void Game::shuffleWorld()
{
	//If score reaced another number divisible by 50
	if (getMiners()[getCurrentMinerIndex()]->getShuffleCounter() < std::floor(getMiners()[getCurrentMinerIndex()]->getScore() / 50)) {
		//Shuffle the world
		getWorld()->shuffle();
		//Increase the shuffle counter for that miner
		getMiners()[getCurrentMinerIndex()]->setShuffleCounter(getMiners()[getCurrentMinerIndex()]->getShuffleCounter() + 1);
	}
}

bool Game::worldEmpty()
{
	//If at any point in the map a value is not 0 (so at least 1 value is still there), return false
	for (int rowIndex = 0; rowIndex < ROWS; rowIndex++) {
		for (int colIndex = 0; colIndex < COLS; colIndex++) {
			if (getWorld()->getWorld()->at(rowIndex).at(colIndex).at(0) != 0)
				return false;
		}
	}

	return true;
}

void Game::printWinner()
{
	int winningMinerIndex = 0;
	int winningMinerScore = 0;
	for (int i = 0; i < getMiners().size(); i++) {
		if (getMiners().at(i)->getScore() > winningMinerScore) {
			winningMinerScore = getMiners().at(i)->getScore();
			winningMinerIndex = i;
		}
	}

	system("cls");
	std::cout << "Miner " << winningMinerIndex + 1 << " won with a score of " << winningMinerScore << "!\n" << std::endl;
	system("pause");
}