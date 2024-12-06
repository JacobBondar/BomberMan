#pragma once

#include <iostream>
#include "Location.h"

class Guard
{
public:
	Guard(Location m_location = { 0 , 0 }, bool m_alive = true);
	Location calcSetNextMove(const Location& loc);
	Location getLocation() const;
	void setGuard(const Location& loc, bool alive);
	bool isAlive() const;
	void killGuard();
	Location returnOg() const;
	void setLocation(const Location& loc);

private:
	Location m_location;
	Location m_ogLocation;
	bool m_alive;

	int lengthDiffer(int firstValue, int secondValue) const;
};
