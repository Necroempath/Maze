#pragma once
#include <thread>
#include "Maze.h"
class Game
{
	static UniquePtr<Random> random;
	static UniquePtr<Maze> maze;

	static void GameLoop(Vector<Moveable*>& moveableObjects);
public:
	static void LaunchGame();
	
};

