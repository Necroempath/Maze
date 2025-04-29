#pragma once
#include "Coord.h"
#include "InputHandler.h"
class Moveable
{
protected:
	Coord position;

public:
	Coord GetPos() const { return position; }

	virtual Coord UpdateDirection() const = 0;

	Item* Move(const Coord& coord, Entity* entity)
	{
		if (dynamic_cast<Passage*>(entity))
		{
			position = coord;
			return nullptr;
		}
		if (dynamic_cast<Item*>(entity))
		{
			position = coord;
			return dynamic_cast<Item*>(entity);
		}
	}

	virtual ~Moveable() = default;
};

class Entity
{
public:
	virtual char GetSymbol() const = 0;
	virtual int GetColorCode() const = 0;

	virtual ~Entity() = default;
};


class Item : public Entity
{
public:
	virtual char GetSymbol() const = 0;
	virtual int GetColorCode() const = 0;
	virtual void Interact() const = 0;

	virtual ~Item() = default;
};

class Key : public Item
{
public:
	char GetSymbol() const override { return 'k'; }
	int GetColorCode() const override { return 13; }

	void Interact() const override {}
};

class Life : public Item
{
public:
	char GetSymbol() const override { return '$'; }
	int GetColorCode() const override { return 3; }

	void Interact() const override {}
};

class Wall : public Entity
{
public:
	char GetSymbol() const override { return '#'; }
	int GetColorCode() const override { return 7; }

	virtual ~Wall() = default;
};

class Passage : public Entity
{
public:
	char GetSymbol() const override { return ' '; }
	int GetColorCode() const override { return 0; }
};

class Player : public Entity, public Moveable
{
	short _health;
	short _speed;
public:
	char GetSymbol() const override { return '@'; }
	int GetColorCode() const override { return 1; }

	Coord UpdateDirection() const override
	{
		return position + InputHandler::GetDirection();
	}
};

class Enemy : public Entity, public Moveable
{
	short _speed;
public:
	char GetSymbol() const override { return '!'; }
	int GetColorCode() const override { return 4; }

	Coord UpdateDirection() const override {}
};

class Exit : public Item
{
public:
	char GetSymbol() const override { return 'E'; }
	int GetColorCode() const override { return 6; }

	void Interact() const override {}
};

