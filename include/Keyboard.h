#pragma once
#include <iostream>
#include <conio.h>

const int UP = 72;
const int DOWN = 80;
const int LEFT = 75;
const int RIGHT = 77;
const int ESCAPE = 27;
const int SPECIAL_KEY = 224;
const int ENTER = 13;

class Keyboard
{
public:
	Keyboard(char c);
	bool keyValid();
	int getDirection();

private:
	char m_direction;
	void special();
	bool checkKey(char c);
};