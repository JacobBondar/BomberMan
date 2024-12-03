#pragma once
#include <iostream>
#include "Location.h"

class Bomb
{
public:
	Bomb(Location loc);
	int getTimer() const;
	void reduceTimer();
	bool explode();
	Location getLocation();

private:
	int m_timer;
	Location m_location;
};
