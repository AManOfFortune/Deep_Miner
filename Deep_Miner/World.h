#pragma once
#include <vector>

class World
{
public:
	//Constructor
	World();

	//Getter & Setter
	void setWorld(std::vector<std::vector<std::vector<int>>> world);
	std::vector<std::vector<std::vector<int>>>* getWorld();

	//Functions
	void initWorld();
	void render(std::vector<std::vector<int>> minerPositions);
	bool posHasMiner(int x, int y, std::vector<std::vector<int>> minerPositions);
	void removeValueAt(int x, int y, int z);
	void shuffle();

private:
	//Variables
	std::vector<std::vector<std::vector<int>>> _world;

	//Functions
	void setColor(int field);
};

