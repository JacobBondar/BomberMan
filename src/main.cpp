#include <iostream>
#include <fstream>
#include <string>
#include <Controller.h>

int main()
{
	auto c = Controller();
	c.run();
}


/*
int main()
{
auto level = std::ifstream("board1.txt");
char c;

while (level.get(c))
{
std::cout << c;
}
}*/