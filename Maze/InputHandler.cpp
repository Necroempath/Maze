#include "InputHandler.h"

Coord InputHandler::GetDirection()
{
	if (_kbhit())
	{
		char input = _getch();

		switch (input)
		{
		case 'w': return Coord(1, 0);
			break;
			case 's': return Coord(-1, 0);
			break;
			case 'a': return Coord(0, -1);
				break;
			case 'd': return Coord(0, 1);
				break;
		}
	}

    return Coord();
}
