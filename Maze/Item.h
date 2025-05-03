#pragma once
#include "Entity.h"
#include "GameData.h"
class Item : public Entity
{
protected:
	bool _isActive = true;

public:
	virtual char GetSymbol() const = 0;
	virtual int GetColorCode() const = 0;
	virtual void OnTouch(GameData& data) = 0;

	bool IsPassable() const override;
	bool IsActive() const;

	virtual ~Item();
};
