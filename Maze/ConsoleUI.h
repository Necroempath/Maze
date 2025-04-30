#pragma once
#include <conio.h>
#include "Item.h"
#include <windows.h> 
#include <iostream>  
#include <chrono>
#include <iomanip>
class ConsoleUI
{
public:
	static Coord GetDirection();

	static void DrawEntityAt(const Coord& pos, Entity* entity);
	
	static void HideCursor();

	static void DisplayInfo(const GameData& data);

	static void SetCursorPosition(SHORT x, SHORT y);
};

