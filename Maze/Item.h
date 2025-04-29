#pragma once
#include "Entity.h"
class Item : public Entity
{
public:
	virtual char GetSymbol() const = 0;
	virtual int GetColorCode() const = 0;
	virtual void OnTouch() const = 0;

	bool IsPassable() const override;

	virtual ~Item();
};
