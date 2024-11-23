#include "io.h"

#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#undef VC_EXTRALEAN
#undef WIN32_LEAN_AND_MEAN

namespace
{
COORD locToCoord(const Location& loc)
{
    auto res = COORD{};
    res.Y = static_cast<short>(loc.row);
    res.X = static_cast<short>(loc.col);
    return res;
}
}

void Screen::resetLocation()
{
    setLocation(Location(0, 0));
}

void Screen::setLocation(const Location& location)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), locToCoord(location));
}
