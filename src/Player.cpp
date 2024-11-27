#include <Player.h>


using std::cout;
using std::endl;

Player::Player(Location newLocation) : m_OriginalPlace(newLocation), m_curPlace(newLocation), m_prePlace (newLocation){}
//----------------------------------------
bool Player::setLocation(int direction)
{
m_prePlace = m_curPlace;
auto direction = _getch();

if (findingIfDirectionVaild(direction))
{
auto direction = _getch();
m_curPlace = updatingLocation(direction);

return true;
}
else
{
//cout << "please type one of the arrows to change the location of the player or b for bomb" << endl;
return false;


}
}
//----------------------------------------
void Player::addPoints(int newPoints)
{
m_points += newPoints;
}
//--------------------------------------
void Player::gotHit()
{
m_lives--;
}
//--------------------------------------
int Player::getPoints() const
{
return m_points;
}
//--------------------------------------
Location Player::getLocation() const
{
return m_curPlace;
}
//-----------------------------------
Location Player::SetOgPlace()
{
m_curPlace = m_OriginalPlace;
return m_curPlace;
}
//---------------------------------
bool Player::findingIfDirectionVaild(int direction)
{

if (direction == 0 || direction == SPECIAL_KEY)
{
return true;
}

else
{
return false;
}
}
//-----------------------------------
Location Player::updatingLocation(int direction)
{

switch (direction)
{
case UP:
{
m_curPlace.row -= 1;
break;
}
case DOWN:
{
m_curPlace.row += 1;
break;
}
case RIGHT:
{
m_curPlace.col += 1;
break;
}
case LEFT:
{
m_curPlace.col -= 1;
break;
}
default:
{
break;
}
}

return m_curPlace;
}
//---------------------------------
int Player::getLives()const
{
return m_lives;
}
//------------------------------
void Player::changePosBack()
{
m_curPlace = m_prePlace;
}
