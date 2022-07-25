#pragma once
#include <vector>
#include "TitleScreen.h"
#include "World.h"

class Game
{
public:
	//Constructor
	Game();

	//Functions
	void start();

private:
	World* _gameWorld;
	std::vector<Miner*> _miners;
	int _currentMinerIndex;

	//Getter & Setter
	void setWorld(World* newWorld);
	void setMiners(std::vector<Miner*> miners);
	void setCurrentMiner(int currentMinerIndex);
	World* getWorld();
	std::vector<Miner*> getMiners();
	int getCurrentMinerIndex();

	//Functions
	void gameLoop();
	void doRoundActions();
	void doStatusEffectActions();
	void addMiner(Miner* miner);
	std::vector<std::vector<int>> getMinerPositions();
	void nextMiner();
	void renderMinersStats();
	void shuffleWorld();
	bool worldEmpty();
	void printWinner();
};