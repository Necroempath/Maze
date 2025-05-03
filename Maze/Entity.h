#pragma once
#include "Coord.h"
class Entity
{
public:
	virtual char GetSymbol() const = 0;
	virtual int GetColorCode() const = 0;
	virtual bool IsPassable() const = 0;

	virtual ~Entity();
};

