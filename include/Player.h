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
Player() = delete;
Player(Location newLocation);
void addPoints(int newPoints);
void setLocation(Location newLocation);
void gotHit();
int getPoints() const;
int getLives()const;
Location getLocation() const;
Location SetOgPlace();
bool setLocation(int direction);
void changePosBack();

private:
Location m_OriginalPlace;
Location m_curPlace;
Location m_prePlace;
int m_lives = 3;
int m_points = 0;

bool findingIfDirectionVaild(int direction);
Location updatingLocation(int direction);
};
