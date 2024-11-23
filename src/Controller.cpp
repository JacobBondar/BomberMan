#include "Controller.h"
#include "KeyBoard.h"


Controller::Controller() {}

void Controller::run()
{
	while (true)
	{
		auto c = _getch();
		Keyboard k(c);

		if (!k.keyValid())
		{
			continue;
		}

		Board b();
		b.placePlayer(c.getDirection());
	}
}