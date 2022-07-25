#pragma once
#include "World.h"
#include <string>
#include <algorithm>

class Miner
{
public:
	//Constructor
	Miner(int x, int y, bool playerControlled);

	//Getters & Setters
	void setName(std::string name);
	void setDescription(std::string description);
	void setPosX(int x);
	void setPosY(int y);
	void setPlayerControlled(bool playerControlled);
	void setStunCounter(int stunCounter);
	void setTeleportCounter(int teleportCounter);
	void setScore(int score);
	void setShuffleCounter(int shuffleCounter);
	std::string getName();
	std::string getDescription();
	int getPosX();
	int getPosY();
	bool isPlayerControlled();
	int getStunCounter();
	int getTeleportCounter();
	int getScore();
	int getShuffleCounter();

	//Functions
	bool moveUp();
	bool moveDown();
	bool moveLeft();
	bool moveRight();
	void fieldEffect(World* gameWorld);
	virtual Miner* clone() = 0;
	virtual void drill(World* gameWorld) = 0;

private:
	//Variables
	std::string _name;
	std::string _description;

	int _x;
	int _y;
	int _score;

	bool _playerControlled;
	int _shuffleCounter;

	int _stunCounter;
	int _teleportCounter;
};

