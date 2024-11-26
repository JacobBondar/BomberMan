#pragma once

#include <iostream>
#include "Location.h"

class Guard
{
public:
	Guard( Location m_location = {0 , 0}, bool m_alive = true );
	void calcSetNextMove();
	Location getLocation() const;
	void setGuard(Location loc, bool alive);
	bool isAlive() const;

private:
	Location m_location;
	bool m_alive;

};
