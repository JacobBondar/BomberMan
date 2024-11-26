#include "Board.h"


Board::Board(Player locPlayer, vector<Guard> locGuards, vector<Location> stones, Location door)
{
	auto level = std::ifstream("game1.txt");
	char c;

	while (level.get(c))
	{
		std::cout << c;
	}
}