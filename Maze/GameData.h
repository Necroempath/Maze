#pragma once
#include "Player.h"
#include "Vector.h"
struct GameData
{
	Player* player;
	Vector<Moveable*>* moveableObjects;
	bool gameOver = false;
	bool gameStoped = false;
	bool enemiesFrozen = false;
	float freezeTime = 0;
	bool knifeActive = false;
	float knifeActivationTime = 0;
	bool exitOpen = false;
	short keysObtained = 0;
	short keysNeeded = 2;
	short speedUpTime = 0;
	float globalTime = 0;
};
