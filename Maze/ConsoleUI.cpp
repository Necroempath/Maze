#include "ConsoleUI.h"

Coord ConsoleUI::GetDirection()
{
	if (_kbhit())
	{
		char input = _getch();

		switch (input)
		{
		case 'w': return Coord(-1, 0);
			break;
			case 's': return Coord(1, 0);
			break;
			case 'a': return Coord(0, -1);
				break;
			case 'd': return Coord(0, 1);
				break;
		}
	}

    return Coord();
}

void ConsoleUI::DrawEntityAt(const Coord& pos, Entity* entity) 
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)pos.GetX(), (short)pos.GetY() });
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), entity->GetColorCode());
	std::cout << entity->GetSymbol();
}

void ConsoleUI::HideCursor() 
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}