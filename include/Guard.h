#pragma once

#include <iostream>
#include "Location.h"

class Guard
{
public:
	Guard(Location m_location = { 0 , 0 }, Location m_ogLocation = { 0 , 0 }, bool m_alive = true);
	void calcSetNextMove();
	Location getLocation() const;
	void setGuard(Location loc, bool alive);
	bool isAlive() const;
	void killGuard();
	Location returnOg();

private:
	Location m_location;
	Location m_ogLocation;
	bool m_alive;

};
