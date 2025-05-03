#pragma once
#include "Moveable.h"

class Player : public Moveable
{
	short _health;

public:
	Player(const Coord& postition, float speed, short health);

	char GetSymbol() const override;

	int GetColorCode() const override;

	bool IsPassable() const override;

	short GetHealth() const;

	void SetHealth(short health);

	Coord UpdateDirection() const override;

	Coord GetDirection() const;
};

