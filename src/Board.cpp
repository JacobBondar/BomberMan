#include "Board.h"

Board::Board() {}

bool Board::createBoard(ifstream& file)
{
	insertIntoBoard(file);

	if (!lookForObjects())
	{
		cout << "Not valid board! Loading the next level..." << endl;
		// add a pause
		return false;
	}
	return true;
}

void Board::eraseBoard()
{
	Screen::resetLocation();
}

void Board::updateBoard(Location player, vector<Guard> guards, vector<Bomb> bombs)
{
	resetBoard();

	m_player = player;
	m_guards = guards;
	m_bombs = bombs;

	setBoard();
}

void Board::resetBoard()
{
	int row = m_player.row;
	int col = m_player.col;

	m_board[row][0][col] = ' ';

	for (int amount = 0; amount < m_guards.size() - 1; amount++)
	{
		row = m_guards[amount].getLocation().row;
		col = m_guards[amount].getLocation().col;

		m_board[row][0][col] = ' ';
	}
}

void Board::setBoard()
{
	int row = m_player.row;
	int col = m_player.col;

	m_board[row][0][col] = '/';

	for (int amount = 0; amount < m_guards.size() - 1; amount++)
	{
		row = m_guards[amount].getLocation().row;
		col = m_guards[amount].getLocation().col;

		m_board[row][0][col] = '!';
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
	}
	return player && door && guard;
}

// @ - stone, / - player, ! - guard, # - limits

void Board::insertIntoLimit(size_t row, size_t col)
{
	m_limit.row = row;
	m_limit.col = col;
}





/*index = 0;
	while (index < m_board.size())
	{
		cout << "help\n";
		if (m_board[index].empty()) cout << "empty" << endl;

		else if (m_board[index][0].length() > maxLength)
		{
			maxLength = m_board[0][index].length();
		}
		index++;
	}if we need to check that the board is a full rectangle  */
