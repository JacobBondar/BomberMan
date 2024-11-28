#pragma once

#include "Board.h"
#include <fstream>
#include <string>
#include "Player.h"
#include "Guard.h"
#include <thread>
#include <chrono>
using namespace std::chrono_literals;


class Controller
{
public:
	Controller();
	void run();


private:
	Board m_board;
	Player m_player;
	vector <Guard> m_guard;

	int endOfTurn();
	bool levelControl(int numLevel);
	void playTurn(bool playerTurn, bool& hurt, bool& dead, bool& won, int numLevel);
	bool endTurnFunction(bool& won, bool& hurt, bool& dead, int numLevel);
};