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
	Player(const Location &newLocation);
	void setToNewLevel(const Location& loc);
	void addPoints(int newPoints);
	bool gotHitDead();
	int getPoints() const;
	int getLives()const;
	Location getLocation() const;
	void SetOgPlace();
	bool setLocation(int direction);
	void changePosBack();
	Location getPrePlace() const;
	Location getOg() const;
	void boughtLife(int amount);

private:
	Location m_OriginalPlace;
	Location m_curPlace;
	Location m_prePlace;
	int m_lives = 2;
	int m_points = 0;

	bool findingIfDirectionVaild(int direction) const;
	void updatingLocation(int direction);
};
