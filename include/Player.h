#pragma once

#include "Location.h"
#include "conio.h"
#include <iostream>
#include "Bomb.h"

using std::cin;


const int UP = 72;
const int DOWN = 80;
const int RIGHT = 77;
const int SPECIAL_KEY = 224;
const int LEFT = 75;

class Player
{
public:
	Player();
	Player(Location newLocation);
	void addPoints(int newPoints);
	bool gotHitDead();
	int getPoints() const;
	int getLives()const;
	Location getLocation() const;
	Location SetOgPlace();
	bool setLocation(int direction); // auto
	void changePosBack();

private:
	Location m_OriginalPlace;
	Location m_curPlace;
	Location m_prePlace;
	int m_lives = 3;
	int m_points = 0;

	bool findingIfDirectionVaild(auto direction);
	Location updatingLocation(int direction);
};
