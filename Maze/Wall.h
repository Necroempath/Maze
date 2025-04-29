#pragma once
#include "Entity.h"
class Wall : public Entity
{
public:
	char GetSymbol() const override;
	int GetColorCode() const override;
	bool IsPassable() const override;
};

