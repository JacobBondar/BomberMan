#include "Bomb.h"

Bomb::Bomb()
{
m_timer = 5;
}
//------------------------
int Bomb::getTimer() const
{
return m_timer;
}
//-------------------------
void Bomb::updateTimer()
{
	m_timer--;
}
//-------------------------
bool Bomb::explode()
{
if (m_timer == 0)
{
return true;
}

return false;
}

Location Bomb::getLocation()
{
	return m_location;
}

void Bomb::setLocation(Location loc)
{
	m_location = loc;
}