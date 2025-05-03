#pragma once
#include "Moveable.h"
class Enemy : public Moveable
{
public:
	Enemy(const Coord& position, float speed);

	char GetSymbol() const override;

	int GetColorCode() const override;

	bool IsPassable() const override;

	Coord UpdateDirection() const override;
};

