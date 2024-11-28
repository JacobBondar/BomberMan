#pragma once
#include <iostream>
#include "Location.h"

class Bomb
{
public:
	Bomb();
	int getTimer() const;
	void updateTimer();
	bool explode();
	Location getLocation();
	void setLocation(Location loc);

private:
	int m_timer;
	Location m_location;

};
