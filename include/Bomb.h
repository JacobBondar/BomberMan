#pragma once
#include <iostream>
#include "Location.h"

class Bomb
{
public:
	Bomb(const Location &loc);
	int getTimer() const;
	void reduceTimer();
	bool explode() const;
	Location getLocation() const;

private:
	int m_timer;
	Location m_location;
};
