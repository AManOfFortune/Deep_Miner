#include <iostream>
#include <algorithm>
#include "World.h"
#include "Config.h"

World::World()
{
	initWorld();
}

void World::setWorld(std::vector<std::vector<std::vector<int>>> world)
{
	_world = world;
}

std::vector<std::vector<std::vector<int>>>* World::getWorld()
{
	return &_world;
}

void World::initWorld()
{
	//Create a vector3d with set sizes
	std::vector<std::vector<std::vector<int>>> tempWorld (ROWS, std::vector<std::vector <int>> (COLS, std::vector<int> (DEPTH)));

	//Fill each spot with a random number between -3 to 9 (without 0)
	for (int rowIndex = 0; rowIndex < ROWS; rowIndex++) {
		for (int colIndex = 0; colIndex < COLS; colIndex++) {
			for (int depthIndex = 0; depthIndex < DEPTH; depthIndex++) {
				do {
					tempWorld[rowIndex][colIndex][depthIndex] = (rand() % 13) - 3;
				} while (tempWorld[rowIndex][colIndex][depthIndex] == 0);
			}
		}
	}

	setWorld(tempWorld);
}

void World::render(std::vector<std::vector<int>> minerPositions)
{
	for (int rowIndex = 0; rowIndex < ROWS; rowIndex++) {

		for (int padding = 0; padding < 3; padding++) {

			for (int colIndex = 0; colIndex < COLS; colIndex++) {
				//Set the colors according to value
				setColor(getWorld()->at(rowIndex).at(colIndex).at(0));

				//Print the miner if that position has a miner, else print the normal number
				if (posHasMiner(colIndex, rowIndex, minerPositions)) {
					if (padding == 0) {
						std::cout << " O---O ";
					}
					else if (padding == 1 && getWorld()->at(rowIndex).at(colIndex).at(0) < 0) {
						std::cout << " |" << getWorld()->at(rowIndex).at(colIndex).at(0) << " | ";
					}
					else if (padding == 1 && getWorld()->at(rowIndex).at(colIndex).at(0) >= 0) {
						std::cout << " | " << getWorld()->at(rowIndex).at(colIndex).at(0) << " | ";
					}
					else {
						std::cout << " O-v-O ";
					}
				}
				else {
					if (padding == 1 && getWorld()->at(rowIndex).at(colIndex).at(0) < 0) {
						std::cout << "  " << getWorld()->at(rowIndex).at(colIndex).at(0) << "   ";
					}
					else if (padding == 1 && getWorld()->at(rowIndex).at(colIndex).at(0) >= 0) {
						std::cout << "   " << getWorld()->at(rowIndex).at(colIndex).at(0) << "   ";
					}
					else {
						std::cout << "       ";
					}
				}
			}
			std::cout << std::endl;
		}
	}

	//Reset the color
	std::cout << "\033[;m";
}

bool World::posHasMiner(int x, int y, std::vector<std::vector<int>> minerPositions)
{
	for (auto& minerIter : minerPositions) {
		if(minerIter[0] == x && minerIter[1] == y)
			return true;
	}

	return false;
}

void World::removeValueAt(int x, int y, int z)
{
	//Erases the value at the given position
	getWorld()->at(y).at(x).erase(getWorld()->at(y).at(x).begin() + z);

	//If that erases the last value, then add a 0 so vector is never empty
	if (getWorld()->at(y).at(x).size() == 0)
		getWorld()->at(y).at(x).push_back(0);
}

void World::shuffle()
{
	for (int rowIndex = 0; rowIndex < ROWS; rowIndex++) {
		for (int colIndex = 0; colIndex < COLS; colIndex++) {
			int option = rand() % 3;

			if ((*getWorld())[rowIndex][colIndex].size() > 1) {
				//Do one of three shuffles for each xy-position in the world
				switch (option)
				{
				case 0: //Shuffle randomly
					std::random_shuffle((*getWorld())[rowIndex][colIndex].begin(), (*getWorld())[rowIndex][colIndex].end());
					break;
				case 1: //Sort ascending
					std::sort((*getWorld())[rowIndex][colIndex].begin(), (*getWorld())[rowIndex][colIndex].end());
					break;
				case 2: //Sort descending
					std::sort((*getWorld())[rowIndex][colIndex].rbegin(), (*getWorld())[rowIndex][colIndex].rend());
					break;
				}
			}
		}
	}
}

void World::setColor(int field)
{
	switch (field)
	{
	case -3:
	case -2:
	case -1:
		std::cout << "\033[101;30m"; //Light Red
		break;
	case 0:
		std::cout << "\033[40;30m"; //Black
		break;
	case 1:
		std::cout << "\033[107;30m"; //White
		break;
	case 2:
		std::cout << "\033[100;30m"; //Grey
		break;
	case 3:
		std::cout << "\033[103;30m"; //Light yellow
		break;
	case 4:
		std::cout << "\033[43;30m"; //Yellow
		break;
	case 5:
		std::cout << "\033[42;30m"; //Green
		break;
	case 6:
		std::cout << "\033[106;30m"; //Light turquoise
		break;
	case 7:
		std::cout << "\033[46;30m"; //Turquoise
		break;
	case 8:
		std::cout << "\033[104;30m"; //Light blue
		break;
	case 9:
		std::cout << "\033[44;30m"; //Blue
		break;
	}
}