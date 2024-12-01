#pragma once
#include <cmath>

/*int lengthDiffer(int firstValue, int secondValue)
{
    return abs(firstValue - secondValue);
}*/

struct Location
{
    int row;
    int col;

    bool isEqual(const Location &other)
    {
        return (*this).row == other.row && (*this).col == other.col; 
    }

    int returnRow(int sign)
    {
        return sign + (*this).row;
    }

    int returnCol(int sign)
    {
        return sign + (*this).col;
    }

    bool isNearBy(Location loc)
    {
        return ((*this).col == loc.col && abs((*this).row - loc.row) == 1 ||
                (*this).row == loc.row && abs((*this).col - loc.col) == 1);
    }

    bool isDiagonal(Location loc)
    {
        return (abs((*this).row - loc.row) == 1 &&
                abs((*this).col - loc.col) == 1);
    }

    bool isHigher(Location loc)
    {
        return (*this).row < loc.row;
    }

    bool isToTheRightOf(Location loc)
    {
        return (*this).col > loc.col;
    }

};
