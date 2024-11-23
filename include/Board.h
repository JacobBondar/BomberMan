#pragma once

#include <vector>
#include "Guard.h"
#include "Player.h"

class Board
{
public:
	Board() = delete;
	Board(Player curPlayer, std::vector<Guard> ogGuards);



private:
	std::vector<Guard> ogGuards;
	std::vector<Guard> curGuards;

	Player ogPlayer;
	Player curPlayer;


};