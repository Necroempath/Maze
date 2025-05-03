#pragma once
#include "Item.h"
class Knife : public Item
{
	char GetSymbol() const override;

	int GetColorCode() const override;

	void OnTouch(GameData& data) override;
};

