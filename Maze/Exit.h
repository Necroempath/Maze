#pragma once
#include "Item.h"
class Exit : public Item
{
public:
	char GetSymbol() const override;

	int GetColorCode() const override;

	void OnTouch(GameData& data) override;
};
