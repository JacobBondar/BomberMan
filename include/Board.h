#pragma once

#include <iostream>
#include <vector>
#include <Guard.h>
#include "Location.h"
#include <fstream>
#include <string>
#include "Bomb.h"
#include "io.h"
#include <cstdlib>
#include <thread>
#include <chrono>
using namespace std::chrono_literals;

using std::vector;
using std::ifstream;
using std::string;

using std::cout; // erase?
using std::endl; // erase?

class Board
{
public:
	Board();
	bool createBoard(ifstream& file);
	void loadAfterMove();
	void loadNextLevel();
	void updateBoardAfterHit(Location newPlayer, Location ogPlayer, vector<Guard> guards);
	void print(int points, int lifes, int level);
	Location getPlayerLoc();
	vector<Location> getGuards();
	vector<Bomb> getBombs();
	void removeStonesExploded();
	//bool isGuardHit(Location Loc);
	bool explodeBomb();
	bool validCell(Location loc);
	void addBomb(Location loc);
	bool foundDoor(Location loc);
	bool checkAllCells(Location loc);
	void removeGuard(int index);
	void reduceBombsTimer();
	void moveObject(Location prev, Location to, char type);
	bool checkIfStone(Location loc);
	void resetBoard();
	void setPlayerLocation(Location loc);

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
	void getRowCol(int row, int col, int& rowReturn, int& colReturn);
	void updatePlayerGuards(char cplayer, char cguard, bool check);
	
};

// @ - stone, / - player, ! - guard, # - limits