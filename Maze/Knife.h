#pragma once
#include "Item.h"
class Knife : public Item
{
	char GetSymbol() const override;

	int GetColorCode() const override;

	bool IsPassable() const override;

	void OnTouch() const override;
};

