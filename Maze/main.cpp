#include "Game.h"
#include <windows.h>

void SetConsoleFullScreen()
{
    HWND hWnd = GetConsoleWindow();
    if (hWnd != nullptr)
    {
        // Нажатие Alt + Enter через посылку сообщения
        keybd_event(VK_MENU, 0x38, 0, 0); // Alt нажата
        keybd_event(VK_RETURN, 0x1C, 0, 0); // Enter нажата
        keybd_event(VK_RETURN, 0x1C, KEYEVENTF_KEYUP, 0); // Enter отпущена
        keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0); // Alt отпущена
    }
}
int main() {
    SetConsoleFullScreen();
	short opt;
	std::cin >> opt;
	system("cls");
	Game::LaunchGame();
	return 0;
}
