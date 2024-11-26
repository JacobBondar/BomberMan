#pragma once

#include <iostream>
#include <vector>
#include "Guard.h"
#include "Player.h"
#include "Location.h";
#include <fstream>;
#include <string>;

using std::vector;

class Board
{
public:
	Board() = delete;
	Board(Player locPlayer, vector<Guard> locGuards, vector<Location> stones, Location door);



private:
	std::vector<Guard> _ogGuards;
	std::vector<Guard> _curGuards;

	Player _ogPlayer;
	Player _curPlayer;


};