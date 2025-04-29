#pragma once
#include "Entity.h"
class Passage : public Entity
{
public:
	char GetSymbol() const override;

	int GetColorCode() const override;

	bool IsPassable() const override;
};
