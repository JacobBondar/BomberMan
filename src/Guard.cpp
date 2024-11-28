#include "Guard.h"

Guard::Guard(Location loc, Location ogLoc, bool alive) : m_location(loc), m_ogLocation(ogLoc), m_alive(alive) {}

void Guard::calcSetNextMove() //algoritem... algoritem... goodluck brother
{
	//algoritem... algoritem... goodluck brother
}

Location Guard::getLocation() const
{
	return m_location;
}

void Guard::setGuard(Location loc, bool alive)
{
	m_ogLocation = loc;
	m_location = loc;
	m_alive = alive;
}

bool Guard::isAlive() const
{
	return m_alive;
}

void Guard::killGuard()
{
	m_alive = false;
}

Location Guard::returnOg()
{
	return m_ogLocation;
}