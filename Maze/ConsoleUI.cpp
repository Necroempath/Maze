#include "ConsoleUI.h"

void ConsoleUI::SetConsoleFullScreen()
{
	HWND hWnd = GetConsoleWindow();

	if (hWnd != nullptr)
	{
		keybd_event(VK_MENU, 0x38, 0, 0);
		keybd_event(VK_RETURN, 0x1C, 0, 0);
		keybd_event(VK_RETURN, 0x1C, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
	}
}

short ConsoleUI::MainMenu()
{
	std::cout << "Type corresponding number to select an option below:\n\n";
	std::cout << "1. New game" << '\n';
	std::cout << "2. Continue" << '\n';
	std::cout << "3. Achievements" << '\n';
	std::cout << "4. Game manual" << '\n';
	std::cout << "5. Exit" << '\n';

	short opt;
	std::cin >> opt;
	std::cin.ignore();

	return opt;
}

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

void ConsoleUI::DisplayInfo(const GameData& data)
{
		/*HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD pos = { 0, static_cast<SHORT>(59 + 1) };
		SetConsoleCursorPosition(hOut, pos);

		std::cout << "Health: " << data.player->GetHealth() << "\n";
		std::cout << "Keys obtained: " << data.keysObtained << "\n";
		std::cout << (data.exitOpen ? "Exit is open\n" : "Exit is closed\n");
		std::cout << "Enemies left: " << data.moveableObjects->Size() << "\n";

		if (data.knifeActive)
			std::cout << "Armed with a knife. Time left: " << data.knifeActivationTime << "\n";
		if (data.enemiesFrozen)
			std::cout << "Enemies frozen. Time left: " << data.freezeTime << "\n";

		std::cout << "Time passed from start: " << data.globalTime << "\n";*/

	const SHORT infoY = 59; 
	const SHORT xVal = 15;  

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

	SetCursorPosition(0, infoY);
	std::cout << "Health: ";
	SetCursorPosition(xVal, infoY);
	std::cout << std::setw(5) << data.player.get()->GetHealth() << "   ";

	SetCursorPosition(0, infoY + 1);
	std::cout << "Keys obtained: ";
	SetCursorPosition(xVal, infoY + 1);
	std::cout << std::setw(5) << data.keysObtained << "   ";

	SetCursorPosition(0, infoY + 2);
	std::cout << "Exit status: ";
	SetCursorPosition(xVal, infoY + 2);
	std::cout << (data.exitOpen ? "OPEN " : "CLOSED");

	SetCursorPosition(0, infoY + 3);
	std::cout << "Enemies left: ";
	SetCursorPosition(xVal, infoY + 3);
	std::cout << std::setw(5) << data.moveableObjects->Size() << "   ";

	if (data.knifeActive)
	{
		SetCursorPosition(0, infoY + 4);
		std::cout << "Knife: ";
		SetCursorPosition(xVal, infoY + 4);
		std::cout << "Active, " << std::fixed << std::setprecision(2)
			<< data.knifeActivationTime << "s left";
	}
	else
	{
		SetCursorPosition(0, infoY + 4);
		std::cout << "Knife: ";
		SetCursorPosition(xVal, infoY + 4);
		std::cout << "Inactive         ";
	}

	if (data.enemiesFrozen)
	{
		SetCursorPosition(0, infoY + 5);
		std::cout << "Enemies: ";
		SetCursorPosition(xVal, infoY + 5);
		std::cout << "Frozen, " << std::fixed << std::setprecision(2)
			<< data.freezeTime << "s left";
	}
	else
	{
		SetCursorPosition(0, infoY + 5);
		std::cout << "Enemies: ";
		SetCursorPosition(xVal, infoY + 5);
		std::cout << "Normal           ";
	}

	SetCursorPosition(0, infoY + 6);
	std::cout << "Time passed: ";
	SetCursorPosition(xVal, infoY + 6);
	std::cout << std::fixed << std::setprecision(2)
		<< data.globalTime << "s       ";
}

void ConsoleUI::SetCursorPosition(SHORT x, SHORT y)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, { x, y });
}