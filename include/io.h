#pragma once

#include "Location.h"

namespace Keys
{
constexpr int ESCAPE = 27;
constexpr int SPECIAL_KEY = 224;
}

namespace SpecialKeys
{
constexpr int UP = 72;
constexpr int DOWN = 80;
constexpr int LEFT = 75;
constexpr int RIGHT = 77;
}

namespace Screen
{
// Reset terminal cursor location to start of the screen (0,0)
void resetLocation();
// Set terminal cursor location to the desired location
void setLocation(const Location& location);
}
