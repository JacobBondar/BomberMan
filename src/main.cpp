#include <iostream>
#include <fstream>
#include <string>
#include <Controller.h>
#include <stdio.h>

int main()
{
    Controller c;
	c.run();
    
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