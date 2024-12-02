#include <iostream>
#include <fstream>
#include <string>
#include <Controller.h>
#include <stdio.h>

int main()
{
    Controller c;
	c.run();

    /*while (1)
    {
        int direction = _getch();

        std::cout << "signal = " << direction << std::endl;
        direction = _getch();
        std::cout << "actual = " << direction << std::endl;
    }*/
    
    
    /*ifstream file, fileLevel;
    string nameLevel;

    file.open("Playlist.txt");
    if (!file)
    {
        std::cerr << "Can't open the main file\n";
        exit(EXIT_FAILURE);
    }


    while (file >> nameLevel)
    {
        cout << nameLevel << endl;
        fileLevel.open(nameLevel);
        if (!fileLevel)
        {
            std::cerr << "Can't open the game file, moving to the next one...\n"; // add timer pls ty
            continue;
        }
    }
    */
	exit(EXIT_SUCCESS);
}