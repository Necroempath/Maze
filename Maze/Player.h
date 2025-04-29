#pragma once
#include "Moveable.h"
#include "ConsoleUI.h"
class Player : public Moveable
{
	short _health;

public:
	Player(const Coord& postition, float speed, short health);

	char GetSymbol() const override;

	int GetColorCode() const override;

	bool IsPassable() const override;

	Coord UpdateDirection() const override;
};

