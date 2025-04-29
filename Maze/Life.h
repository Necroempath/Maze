#pragma once
#include "Item.h"
class Life : public Item
{
public:
	char GetSymbol() const override;
	int GetColorCode() const override;

	void OnTouch() const override;
};


