#include "Board.h"

Board::Board() {}

bool Board::createBoard(ifstream& file)
{
	insertIntoBoard(file);

	if (!lookForObjects())
	{
		cout << "Not valid board! Loading the next level..." << endl;
		std::this_thread::sleep_for(200ms);
		return false;
	}
	return true;
}

void Board::loadAfterMove()
{
	Screen::resetLocation();
}

void Board::loadNextLevel()
{
	system("cls");
}

void Board::updateBoardAfterExploded(Location player, vector <Guard> guards)
{
	updatePlayerGuards(' ', ' ', false);

	m_player = player;
	
	for (int index = 0; index < guards.size(); index++)
	{
		m_guards[index] = guards[index].getLocation();
	}

	updatePlayerGuards('/', '!', true);
}

void Board::updatePlayerGuards(char cplayer, char cguard, bool check)
{
	int row, col;
	getRowCol(m_player.row, m_player.col, row, col);
	m_board[row][0][col] = cplayer;

	for (int amount = 0; amount < m_guards.size(); amount++)
	{
		getRowCol(m_guards[amount].row, 
			m_guards[amount].col, row, col);

		m_board[row][0][col] = cguard;
	}

	if(check) m_bombs.clear();
}

void Board::removeGuard(int index)
{
	int row, col;
	getRowCol(m_guards[index].row, m_guards[index].col, row, col);
	m_board[row][0][col] = ' ';

	m_guards.erase(m_guards.begin() + index);
	m_guards.shrink_to_fit();
}

void Board::print(int points, int lifes, int level)
{
	for (int row = 0; row < m_limit.row + 1; row++)
	{
		for (int col = 0; col < m_limit.col + 1; col++)
		{
			cout << m_board[row][0][col];
		}
	}
	cout << "\nPoints: " << points << "\nLifes <3: " << lifes 
		<< "\nlevel: " << level << endl;
}

Location Board::getPlayerLoc()
{
	return m_player;
}

vector<Location> Board::getGuards()
{
	return m_guards;
}

vector<Bomb> Board::getBombs()
{
	return m_bombs;
}

bool Board::isGuardHit(Location loc)
{
	if (loc.isEqual(m_bombs[0].getLocation()))
	{
		int row, col;
		getRowCol(loc.row, loc.col, row, col);
		m_board[row][0][col] = ' ';
		return true;
	}
	return false;
}

int Board::checkHowManyGuardFinito(Location loc)
{
	int cell, row, col, guard_down = 0;
	for (cell = 0; cell < m_stones.size() + 1; cell++)
	{
		if (loc.isEqual(m_stones[cell]))
		{
			getRowCol(m_stones[cell].row,
				m_stones[cell].col, row, col);

			m_board[row][0][col] = ' ';
			m_stones.erase(m_stones.begin() + cell);
		}
	}
	m_guards.shrink_to_fit();
	m_stones.shrink_to_fit();

	return guard_down;
	return 0;
}

void Board::addBomb(Location loc)
{
	Bomb b(loc);
	m_bombs.push_back(b);
}

bool Board::validCell(Location loc)
{
	int row, col;
	getRowCol(loc.row, loc.col, row, col);

	if (m_board[row][0][col] == '#' || m_board[row][0][col] == '@') return false;

	if (row > m_limit.row || col > m_limit.col || row < 0 || col < 0) return false;

	return true;
}

bool Board::foundDoor(Location loc)
{
	int row, col;
	getRowCol(loc.row, loc.col, row, col);

	return m_board[row][0][col] == 'D';
}





void Board::insertIntoBoard(ifstream& file)
{
	auto rowInGame = std::string();
	int index = 0, maxLength = 0;

	while (getline(file, rowInGame)) // add the board
	{
		rowInGame += "\n";

		if (index >= m_board.size()) m_board.resize(index + 1);

		m_board[index].push_back(rowInGame);
		index++;
	}
	cout << m_board.size() - 1 << endl << m_board[0][0].size() - 2 << endl; // '\n'

	insertIntoLimit(m_board.size() - 1, m_board[0][0].size() - 2);
}

bool Board::lookForObjects()
{
	bool player = false, guard = false, door = false;
	int guardCell = 0, stoneCell = 0, playerCounter = 0, doorCounter = 0;
	size_t position = 0;

	for (int row = 0; row < m_limit.row + 1; row++)
	{
		position = m_board[row][0].find('/', 0);
		if (position != std::string::npos)
		{
			m_player.row = row;
			m_player.col = position;
			player = true;
			playerCounter++;
			if (playerCounter > 1) return false;
		}
		
		position = m_board[row][0].find('D', 0);
		if (position != std::string::npos)
		{
			door = true;
			doorCounter++;
			if (doorCounter > 1) return false;
		}

		position = m_board[row][0].find('!', 0);
		if (position != std::string::npos)
		{
			if (guardCell >= m_guards.size()) m_guards.resize(++guardCell);

			m_guards[guardCell - 1].row = row;
			m_guards[guardCell - 1].col = (int)position;
			guard = true;
		}

		position = m_board[row][0].find('@', 0);
		if (position != std::string::npos)
		{
			if (stoneCell >= m_stones.size()) m_stones.resize(++stoneCell);

			m_stones[stoneCell - 1].row = row;
			m_stones[stoneCell - 1].row = (int)position;
		}
	}
	return player && door && guard;
}

void Board::insertIntoLimit(size_t row, size_t col)
{
	m_limit.row = row;
	m_limit.col = col;
}

void Board::getRowCol(int row, int col,int &rowReturn, int &colReturn)
{
	rowReturn = row;
	colReturn = col;
}

bool Board::checkAllCells(Location check)
{
	Location loc = m_bombs[0].getLocation();

	Location sides[5] = { loc, loc.returnRow(1), loc.returnRow(-1),
							loc.returnCol(1), loc.returnCol(-1) };

	for (int index = 0; index < 5; index++)
	{
		if (sides[index].isEqual(check)) return true;
	}
	return false;
}

bool Board::explodeBomb()
{
	return m_bombs[0].explode();
}

void Board::reduceBombsTimer()
{
	for (int index = 0; index < m_bombs.size(); index++)
	{
		m_bombs[index].updateTimer();
	}
}