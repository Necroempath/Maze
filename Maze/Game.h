#pragma once
#include <chrono>
#include <thread>
#include "Maze.h"
class Game
{
	static UniquePtr<Random> random;
	static UniquePtr<Maze> maze;

	static void GameLoop(GameData& data);
public:
	static void LaunchGame();
	
};

