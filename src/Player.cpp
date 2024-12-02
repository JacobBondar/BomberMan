#include <Player.h>


using std::cout;
using std::endl;

Player::Player() : m_OriginalPlace({0 , 0}), m_curPlace({ 0 , 0 }), m_prePlace({ 0 , 0 }) {}

Player::Player(Location newLocation) : m_OriginalPlace(newLocation), m_curPlace(newLocation), m_prePlace (newLocation){}
//----------------------------------------
bool Player::setLocation(int direction)
{
	m_prePlace = m_curPlace;

	if (findingIfDirectionVaild(direction))
	{
		direction = _getch();
		updatingLocation(direction);

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
bool Player::gotHitDead()
{
	m_lives--;
	if (m_lives == 0) return true;
	return false;
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
void Player::SetOgPlace()
{
	m_curPlace = m_OriginalPlace;
}
//---------------------------------
bool Player::findingIfDirectionVaild(int direction)
{

	if (direction == 0 || direction == SPECIAL_KEY)
	{
		return true;
	}
	return false;
}
//-----------------------------------
void Player::updatingLocation(int direction)
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

Location Player::getPrePlace()
{
	return m_prePlace;
}

Location Player::getOg()
{
	return m_OriginalPlace;
}