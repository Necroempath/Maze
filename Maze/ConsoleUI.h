#pragma once
#include <conio.h>
#include "Entity.h"
#include <windows.h> 
#include <iostream>  
class ConsoleUI
{
public:
	static Coord GetDirection();

	static void DrawEntityAt(const Coord& pos, Entity* entity);
	
	static void HideCursor();
};

