#include "Keyboard.h"


Keyboard::Keyboard(char c)
{
	if (c == 0 || c == SPECIAL_KEY) special();

	else
	{
		if (checkKey(c)) m_direction = c;
		else m_direction = NULL;
	}
}

void Keyboard::special()
{
	const auto c = _getch();

	if (m_direction == UP) m_direction = '1';

	if (m_direction == DOWN) m_direction = '2';

	if (m_direction == LEFT) m_direction = '3';

	if (m_direction == RIGHT) m_direction = '4';

	m_direction = NULL; // invalid input
}

bool Keyboard::keyValid()
{
	if (m_direction == NULL) return false;
	return true;
}

bool Keyboard::checkKey(char c)
{
	if (c != 'b') // if you people discover more char, add here with ||
	{
		return false;
	}

	return true;
}

int Keyboard::getDirection()
{
	return m_direction;
}
