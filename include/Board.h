#pragma once

#include <iostream>
#include <vector>
#include "Location.h";
#include <fstream>;
#include <string>;
#include "Guard.h"
#include "Bomb.h"
#include "Player.h"
#include "io.h"

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
	void eraseBoard();
	void updateBoard(Location player, vector<Guard> guards, vector<Bomb> bombs);
	//void print(int points, int lifes, int level);
	//void printString();
	//Location getPlayerLoc();
	//bool validCell(Location loc);
	//void addBomb(Location Loc);

private:
	vector<vector<string>> m_board;
	vector<Guard> m_guards;
	vector<Bomb> m_bombs;
	Location m_player = { 0, 0 };
	Location m_limit = { 0, 0 };
	
	void insertIntoBoard(ifstream& file);
	bool lookForObjects();
	void insertIntoLimit(size_t row, size_t col);
	void resetBoard();
	void setBoard();
};
