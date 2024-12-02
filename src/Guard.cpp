#include "Guard.h"

Guard::Guard(Location loc, Location ogLoc, bool alive) : m_location(loc), m_ogLocation(ogLoc), m_alive(alive) {}

Location Guard::calcSetNextMove(Location locPlayer) //algoritem... algoritem... goodluck brother... ez kissy face ;-)
{
	Location prev = m_location;

	if (m_location.isEqual(locPlayer));

	else if (m_location.isNearBy(locPlayer)) m_location = locPlayer;

	else if (m_location.isDiagonal(locPlayer));

	else
	{
		int xLength = lengthDiffer(m_location.col, locPlayer.col);
		int yLength = lengthDiffer(m_location.row, locPlayer.row);

		if (yLength > xLength)
		{
			if (m_location.isHigher(locPlayer)) m_location.row++;
			else m_location.row--;
		}
		else
		{
			if (m_location.isToTheRightOf(locPlayer)) m_location.col--;
			else m_location.col++;
		}
	}
	return prev;
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

int Guard::lengthDiffer(int firstValue, int secondValue)
{
	return abs(firstValue - secondValue);
}