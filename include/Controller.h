#pragma once

#include "Board.h"
#include "Player.h"
#include "Guard.h"
#include <fstream>
#include <string>
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

	void endOfTurn(bool& won, bool& hurt, bool& dead, bool player);
	bool levelControl(int numLevel);
	void playTurn(bool playerTurn, bool& hurt, bool& dead, bool& won,
		int numLevel);
	void checkIfFileOpened(ifstream& file);
	bool checkIfGameOpened(ifstream& file);
	bool checkIfBoardValid(ifstream& file);
	void wonGame();
	bool lostGame();
	void endGame(ifstream& file);
	int insertNewGuards();
	bool playerPlaysTurn(int numLevel);
	bool guardPlaysTurn(int numLevel, bool& won, bool& hurt, bool& dead,
		bool playerTurn, int guardCell);
	bool controlTheExplosion(bool& dead, bool& hurt);
	void checkIfPlayerHitGuard(bool& dead, bool& hurt);
};