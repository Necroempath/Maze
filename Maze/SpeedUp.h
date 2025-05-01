#pragma once
#include "Item.h"
class SpeedUp : public Item
{
	char GetSymbol() const override;

	int GetColorCode() const override;

	void OnTouch(GameData& data) override;
};

