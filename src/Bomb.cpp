#include "Bomb.h"

//-----------------------------------------------------------------------------

Bomb::Bomb(const Location& loc) : m_location(loc)
{
	m_timer = 5;
}

//-----------------------------------------------------------------------------

int Bomb::getTimer() const
{
	return m_timer;
}

//-----------------------------------------------------------------------------

void Bomb::reduceTimer()
{
	m_timer--;
}

//-----------------------------------------------------------------------------

bool Bomb::explode() const
{
	if (m_timer == 0) return true;

	return false;
}

//-----------------------------------------------------------------------------

Location Bomb::getLocation() const
{
	return m_location;
}