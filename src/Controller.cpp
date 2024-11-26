#include "Controller.h"
#include "KeyBoard.h"


#include <fstream>;
#include <string>;

Controller::Controller() {}

void Controller::run()
{
	Board b();
	while (true)
	{
		auto c = _getch();
		Keyboard k(c);

		if (!k.keyValid())
		{
			continue;
		}

		
		b.placePlayer(c.getDirection());
	}
}