#include "Board.h"

Board::Board(ifstream& file)
{
	insertIntoBoard(file);
	
	if (!lookForObjects())
	{
		cout << "Not valid board!" << endl;
	}
	
	else
	{

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
	int guardCell = 0, stoneCell = 0;

	for (int row = 0; row < m_limit[1].row; row++)
	{
		for (int col = 0; col < m_limit[1].col; col++)
		{
			if (!player && m_board[row][col].find('/', 0))
			{
				m_player.row = row;
				m_player.row = col;
				player = true;
			}

			if (!door && m_board[row][col].find('D', 0)) door = true;

			if (m_board[row][col].find('!', 0))
			{
				guardCell = insertValuesInVactor(row, col, guardCell, guard);
			}

			if (m_board[row][col].find('@', 0))
			{
				if (stoneCell >= m_stone.size()) m_stone.resize(stoneCell + 1);

				m_stone[stoneCell] = {row, col};
				stoneCell++;
			}
		}
	}
	return player && door && guard;
}

// @ - stone, / - player, ! - guard, # - limits

void Board::insertIntoLimit(int row, int col)
{
	m_limit[0].row = m_limit[0].col = 0;
	m_limit[1].row = row;
	m_limit[1].col = col;
}

void Board::insertValuesInGuard(vector<void*> m_bombs ,int row, int col, int &cell, bool &exists)
{
	if (cell >= m_bombs.size()) m_guards.resize(++cell);
	
	m_guards[cell - 1].setLocation({ row, col }, true);
	exists = true;
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

