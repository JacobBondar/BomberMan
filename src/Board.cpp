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

void Board::updateBoard(Location player, vector<Guard> guards, vector<Bomb> bombs,
	vector<Location> stones)
{
	updatePlayerGuards(' ', ' ', false);

	m_player = player;
	m_guards = guards;
	m_bombs = bombs;
	m_stones = stones;

	updatePlayerGuards('/', '!', true);
}

void Board::updatePlayerGuards(char cplayer, char cguard, bool check)
{
	int row, col;
	getRowCol(m_player.row, m_player.col, row, col);
	m_board[row][0][col] = cplayer;

	for (int amount = 0; amount < m_guards.size() - 1; amount++)
	{
		if (check && !m_guards[amount].isAlive())
		{
			m_guards.erase(m_guards.begin() + amount);
			continue;
		}

		getRowCol(m_guards[amount].getLocation().row, 
			m_guards[amount].getLocation().col, row, col);

		m_board[row][0][col] = cguard;
	}

	for (int bomb_cell = 0; check && bomb_cell < m_bombs.size() - 1; bomb_cell++)
	{
		if (m_bombs[bomb_cell].explode())
		{
			m_bombs.erase(m_bombs.begin() + bomb_cell);
			continue;
		}

		m_bombs[bomb_cell].updateTimer();
	}
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
			if (guardCell >= m_bombs.size()) m_guards.resize(++guardCell);

			m_guards[guardCell - 1].setGuard({ row, (int)position }, true);
			guard = true;
		}

		position = m_board[row][0].find('@', 0);
		if (position != std::string::npos)
		{
			if (stoneCell >= m_bombs.size()) m_bombs.resize(++stoneCell);

			m_bombs[stoneCell - 1].setLocation({ row, (int)position });
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