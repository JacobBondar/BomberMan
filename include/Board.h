#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include <thread>
#include <chrono>
#include "Location.h"
#include "Bomb.h"
#include "io.h"
#include <Guard.h>
using namespace std::chrono_literals;

using std::vector;
using std::ifstream;
using std::string;

using std::cout;
using std::endl;

class Board
{
public:
	Board();
	bool createBoard(ifstream& file);
	void resetStartLoction() const;
	void eraseBoard() const;
	void updateBoardAfterHit(const Location& newPlayer,
		const Location& ogPlayer, vector <Guard> guards);
	void print(int points, int lifes, int level);
	Location getPlayerLoc() const;
	vector<Location> getGuards() const;
	void removeStonesExploded();
	bool explodeBomb();
	bool validCell(const Location& loc) const;
	void addBomb(const Location& loc);
	bool foundDoor(const Location& loc) const;
	bool checkAllCells(const Location& loc);
	void removeGuard(int index);
	void removeBomb();
	void reduceBombsTimer();
	bool moveObject(const Location& prev, const Location& to, char type);
	bool checkIfStone(const Location& loc) const;
	void resetBoard();
	void addExplodedBomb();
	void printFile(string name) const;
	void setLocPlayer(const Location& loc);
	void setLocGuard(int index, const Location& loc);
	void printFinalScore(int score, int lifes) const;

private:
	vector<vector<string>> m_board;
	vector<Location> m_guards;
	vector<Bomb> m_bombs;
	vector<Location> m_stones;
	Location m_player = { 0, 0 };
	Location m_limit = { 0, 0 };

	void insertIntoBoard(ifstream& file);
	bool lookForObjects();
	void insertIntoLimit(size_t row, size_t col);
	void getRowCol(int row, int col, int& rowReturn, int& colReturn) const;
	void updatePlayerGuards(char cplayer, char cguard);
	void updateGuards(char c);
	void updateBombs(char c);
	void insertStoneToPrint();
	void insertBombsToPrint();
	void insertGuardsToPrint();
	void printRowsRemoveStars();
	bool lookForPlayer(int row, bool& player, int& playerCounter);
	bool lookForDoor(int row, bool& door, int& doorCounter);
	void LookForGuards(int row, bool& guard, int& guardCell);
	void LookForStones(int row, int& stoneCell);
};