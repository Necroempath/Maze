#pragma once
#include "Item.h"
class Key : public Item
{
public:
	char GetSymbol() const override;

	int GetColorCode() const override;

	void OnTouch(GameData& data) const override;
};

