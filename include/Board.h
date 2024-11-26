#pragma once

#include <iostream>
#include <vector>
#include "Location.h";
#include <fstream>;
#include <string>;
#include <Guard.h>
#include <Bomb.h>
#include <Player.h>

using std::vector;
using std::ifstream;
using std::string;

using std::cout; // erase?
using std::endl; // erase?

class Board
{
public:
	Board() = delete;
	Board(ifstream& file);
	void eraseBoard();
	void updateBoard(Location player, vector<Guard> m_guards, vector<Bomb> m_bombs,
		vector<Location> m_stone);
	void print();
	void printString();

private:
	vector<vector<string>> m_board;
	vector<Guard> m_guards;
	vector<Bomb> m_bombs;
	vector<Location> m_stone;
	Location m_player;
	Location m_limit[2]; // [0] - top left, [1] - top right
						 // if rectangle always perfect, take down arr and leave one
	//bool player;
	//bool door;
	
	bool validCell(Location loc);
	void insertIntoBoard(ifstream& file);
	bool lookForObjects();
	void insertIntoLimit(int row, int col);
	void insertValuesInGuard(int row, int col, int& cell, bool& exists);
};