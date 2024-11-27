#include <iostream>
#include <fstream>
#include <string>
#include <Controller.h>
#include <stdio.h>

#include <Board.h> // erase!!!!!

int main()
{
	//auto c = Controller();
	//c.run();
	auto file = std::ifstream("game1.txt");

	auto b = Board();

	b.createBoard(file);

	exit(EXIT_SUCCESS);
}

/*
* auto list = std::ifstream("Playlist.txt");

	if (!list.is_open())
	{
		//-----
	}

	auto levelName = std::string();
	auto rowInGame = std::string();
	char c;

	while (getline(list, levelName))
	{
		if (list.fail()) break;

		auto level = std::ifstream(levelName);
		if (!level.is_open())
		{
			//-----
		}

		while (getline(level, rowInGame))
		{
			std::cout << rowInGame << std::endl;
		}
	}
*/
