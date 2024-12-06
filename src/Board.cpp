#include "Board.h"
#include <cstdlib>

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

void Board::resetStartLoction()
{
	Screen::resetLocation();
}

void Board::eraseBoard()
{
	system("cls");
}

void Board::updateBoardAfterHit(Location newPlayer, Location ogPlayer, vector <Guard> guards)
{
	m_player = newPlayer;
	updatePlayerGuards(' ', ' ');

	m_player = ogPlayer;
	for (int index = 0; index < guards.size(); index++)
	{
		m_guards[index] = guards[index].returnOg();
	}

	updatePlayerGuards('/', '!');
}

void Board::updatePlayerGuards(char cplayer, char cguard)
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

	for (int index = 0; index < m_bombs.size(); index++)
	{
		getRowCol(m_bombs[index].getLocation().row,
			m_bombs[index].getLocation().col, row, col);

		m_board[row][0][col] = cplayer;
	}
	m_bombs.clear();
}

void Board::removeGuard(int index)
{
	int row, col;
	getRowCol(m_guards[index].row, m_guards[index].col, row, col);
	m_board[row][0][col] = ' ';

	m_guards.erase(m_guards.begin() + index);
}

void Board::print(int points, int lifes, int level)
{
	resetStartLoction();

	int row, col, index;
	size_t position = 0;

	for (int cell = 0; cell < m_stones.size(); cell++)
	{
		getRowCol(m_stones[cell].row, m_stones[cell].col,
			row, col);
		m_board[row][0][col] = '@';
	}

	for (int cell = 0; cell < m_bombs.size(); cell++)
	{
		getRowCol(m_bombs[cell].getLocation().row, m_bombs[cell].getLocation().col,
			row, col);
		if (m_player.isEqual(m_bombs[cell].getLocation())) m_board[row][0][col] = '%';

		else m_board[row][0][col] = m_bombs[cell].getTimer() + 48;
	}

	for (int cell = 0; cell < m_guards.size(); cell++)
	{
		getRowCol(m_guards[cell].row, m_guards[cell].col,
			row, col);
		m_board[row][0][col] = '!';
	}
	
	for (row = 0; row < m_limit.row + 1; row++)
	{
		cout << m_board[row][0];

		index = 0;
		position = m_board[row][0].find('*', index);
		while (position != std::string::npos)
		{
			m_board[row][0][(int)position] = ' ';
			index++;
			position = m_board[row][0].find('*', index);
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

void Board::removeStonesExploded()
{
	int cell, row, col;

	for (cell = 0; cell < m_stones.size(); cell++)
	{
		if (checkAllCells(m_stones[cell]))
		{
			getRowCol(m_stones[cell].row,
				m_stones[cell].col, row, col);

			m_board[row][0][col] = ' ';
			m_stones.erase(m_stones.begin() + cell);
			cell--;
		}
	}
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

	if (row > m_limit.row || col > m_limit.col || row < 0 || col < 0) return false;

	if (m_board[row][0][col] == '#' || m_board[row][0][col] == '@') return false;
	
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
	int index = 0;

	while (getline(file, rowInGame))
	{
		rowInGame += "\n";

		if (index >= m_board.size()) m_board.resize(index + 1);

		m_board[index].push_back(rowInGame);
		index++;
	}

	insertIntoLimit(m_board.size() - 1, m_board[0][0].size() - 2);
}

bool Board::lookForObjects()
{
	bool player = false, guard = false, door = false;
	int guardCell = 0, stoneCell = 0, playerCounter = 0, doorCounter = 0, col;
	size_t position = 0;

	for (int row = 0; row < m_limit.row + 1; row++)
	{
		position = m_board[row][0].find('/', 0);
		if (position != std::string::npos)
		{
			m_player.row = row;
			m_player.col = (int)position;
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

		col = 0;
		while (col < m_limit.col + 1)
		{
			position = m_board[row][0].find('!', col);
			if (position != std::string::npos)
			{
				if (guardCell >= m_guards.size()) m_guards.resize(++guardCell);

				m_guards[guardCell - 1].row = row;
				m_guards[guardCell - 1].col = (int)position;
				guard = true;
				col = (int)position + 1;
			}
			else break;
		}
		
		col = 0;
		while (col < m_limit.col + 1)
		{
			position = m_board[row][0].find('@', col);
			if (position != std::string::npos)
			{
				if (stoneCell >= m_stones.size()) m_stones.resize(++stoneCell);

				m_stones[stoneCell - 1].row = row;
				m_stones[stoneCell - 1].col = (int)position;
				col = (int)position + 1;
			}
			else break;
		}
	}
	return player && door && guard;
}

void Board::insertIntoLimit(size_t row, size_t col)
{
	m_limit.row = (int)row;
	m_limit.col = (int)col;
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
	if (m_bombs.empty()) return false;

	return m_bombs[0].explode();
}

void Board::reduceBombsTimer()
{
	for (int index = 0; index < m_bombs.size(); index++)
	{
		m_bombs[index].reduceTimer();
	}
}

bool Board::moveObject(Location prev, Location to, char type)
{
	bool flag = foundDoor(to);
	int rowPrev, colPrev, rowTo, colTo;
	getRowCol(prev.row, prev.col, rowPrev, colPrev);
	getRowCol(to.row, to.col, rowTo, colTo);

	m_board[rowPrev][0][colPrev] = ' ';
	m_board[rowTo][0][colTo] = type;
	return flag;
}

bool Board::checkIfStone(Location loc)
{
	int row, col;
	getRowCol(loc.row, loc.col, row, col);

	return m_board[row][0][col] == '@';
}

void Board::resetBoard()
{
	m_board.clear();
	m_guards.clear();
	m_bombs.clear();
	m_stones.clear();
	m_player = { 0, 0 };
	m_limit = { 0, 0 };
}

void Board::setPlayerLocation(Location loc)
{
	m_player = loc;
}

void Board::removeBomb()
{
	m_bombs.erase(m_bombs.begin() + 0);
}

void Board::addExplodedBomb()
{
	int row, col;
	Location loc = m_bombs[0].getLocation();

	Location sides[5] = { loc, loc.returnRow(1), loc.returnRow(-1),
							loc.returnCol(1), loc.returnCol(-1) };

	for (int index = 0; index < 5; index++)
	{
		getRowCol(sides[index].row, sides[index].col, row, col);

		if (validCell(sides[index]) && m_board[row][0][col] != 'D') 
			m_board[row][0][col] = '*';
	}
}

void Board::setLocGuard(int index, Location loc)
{
	m_guards[index] = loc;
}

void Board::printFile(string name)
{
	ifstream file(name);
	if (!file)
	{
		std::cerr << "Can't open the file...\n";
		exit(EXIT_FAILURE);
	}

	std::string sentence;

	while (getline(file, sentence))
	{
		cout << sentence << endl;
	}
}

void Board::setLocPlayer(Location loc)
{
	m_player = loc;
}

void Board::printFinalScore(int score, int lifes)
{
	cout << "You Finished with: " << score << " points, and " << lifes << " lifes!\n";
}