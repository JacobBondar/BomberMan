#pragma once
#include <cmath>

struct Location
{
    int row;
    int col;

    bool isEqual(const Location& other);
    Location returnRow(int sign);
    Location returnCol(int sign);
    bool isNearBy(Location loc);
    bool isDiagonal(Location loc);
    bool isHigher(Location loc);
    bool isToTheRightOf(Location loc);
};
