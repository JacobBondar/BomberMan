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
