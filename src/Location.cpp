#include "Location.h"

//-----------------------------------------------------------------------------

bool Location::isEqual(const Location& other)
{
    return (*this).row == other.row && (*this).col == other.col;
}

//-----------------------------------------------------------------------------

Location Location::returnRow(int sign)
{
    Location temp((*this).row + sign, (*this).col);
    return temp;
}

//-----------------------------------------------------------------------------

Location Location::returnCol(int sign)
{
    Location temp((*this).row, (*this).col + sign);
    return temp;
}

//-----------------------------------------------------------------------------

bool Location::isNearBy(Location loc)
{
    return ((*this).col == loc.col && abs((*this).row - loc.row) == 1 ||
        (*this).row == loc.row && abs((*this).col - loc.col) == 1);
}

//-----------------------------------------------------------------------------

bool Location::isDiagonal(Location loc)
{
    return (abs((*this).row - loc.row) == 1 &&
        abs((*this).col - loc.col) == 1);
}

//-----------------------------------------------------------------------------

bool Location::isHigher(Location loc)
{
    return (*this).row < loc.row;
}

//-----------------------------------------------------------------------------

bool Location::isToTheRightOf(Location loc)
{
    return (*this).col > loc.col;
}