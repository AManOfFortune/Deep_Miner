#include "Miner.h"
#include "Config.h"

Miner::Miner(int x, int y, bool playerControlled)
{
	setName("Miner");
	setDescription("Standard Miner");
	setPosX(x);
	setPosY(y);
	setPlayerControlled(playerControlled);
	setStunCounter(0);
	setTeleportCounter(0);
	setScore(0);
	setShuffleCounter(0);
}

void Miner::setName(std::string name)
{
	_name = name;
}

void Miner::setDescription(std::string description)
{
	_description = description;
}

void Miner::setPosX(int x)
{
	if (x < 0)
		_x = 0;
	else if (x >= COLS)
		_x = COLS - 1;
	else
		_x = x;
}

void Miner::setPosY(int y)
{
	if (y < 0)
		_y = 0;
	else if (y >= ROWS)
		_y = ROWS - 1;
	else
		_y = y;
}

void Miner::setPlayerControlled(bool playerControlled)
{
	_playerControlled = playerControlled;
}

void Miner::setStunCounter(int stunCounter)
{
	if (stunCounter < 0)
		_stunCounter = 0;
	else
		_stunCounter = stunCounter;
}

void Miner::setTeleportCounter(int teleportCounter)
{
	if (teleportCounter < 0)
		_teleportCounter = 0;
	else
		_teleportCounter = teleportCounter;
}

void Miner::setScore(int score)
{
	if (score < 0)
		_score = 0;
	else
		_score = score;
}

void Miner::setShuffleCounter(int shuffleCounter)
{
	_shuffleCounter = shuffleCounter;
}

std::string Miner::getName()
{
	return _name;
}

std::string Miner::getDescription()
{
	return _description;
}

int Miner::getPosX()
{
	return _x;
}

int Miner::getPosY()
{
	return _y;
}

bool Miner::isPlayerControlled()
{
	return _playerControlled;
}

int Miner::getStunCounter()
{
	return _stunCounter;
}

int Miner::getTeleportCounter()
{
	return _teleportCounter;
}

int Miner::getScore()
{
	return _score;
}

int Miner::getShuffleCounter()
{
	return _shuffleCounter;
}

bool Miner::moveUp()
{
	int oldY = getPosY();
	setPosY(getPosY() - 1);

	if (getPosY() == oldY) return false;
	return true;
}

bool Miner::moveDown()
{
	int oldY = getPosY();
	setPosY(getPosY() + 1);

	if (getPosY() == oldY) return false;
	return true;
}

bool Miner::moveLeft()
{
	int oldX = getPosX();
	setPosX(getPosX() - 1);

	if (getPosX() == oldX) return false;
	return true;
}

bool Miner::moveRight()
{
	int oldX = getPosX();
	setPosX(getPosX() + 1);

	if (getPosX() == oldX) return false;
	return true;
}

void Miner::fieldEffect(World* gameWorld)
{
	switch (gameWorld->getWorld()->at(getPosY()).at(getPosX()).at(0))
	{
	case -3: //Loose 30 score
		setScore(getScore() - 30);
		break;
	case -2: //Teleport bot to first lowest field
		setTeleportCounter(getTeleportCounter() + 1);
		break;
	case -1: //Stun the bot for one round (meaning he cannot drill)
		setStunCounter(getStunCounter() + 2);
		break;
	default: //On all other fields increase score
		setScore(getScore() + gameWorld->getWorld()->at(getPosY()).at(getPosX()).at(0));
		break;
	}

	//Remove field
	gameWorld->removeValueAt(getPosX(), getPosY(), 0);
}