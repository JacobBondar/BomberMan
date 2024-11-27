#pragma once
#include <iostream>

class Bomb
{
public:
Bomb();
int getTimer() const;
void updateTimer();
bool explode();
private:
int m_timer;

};
