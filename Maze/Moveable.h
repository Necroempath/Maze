#pragma once
#include "Entity.h"
class Moveable : public Entity
{
protected:
	Coord _position;
	float _speed;
	float _timeSinceLastMove = 0.0f;

public:
	Moveable(const Coord& position, float speed) : _position(position), _speed(speed) {}

	void SetSpeed(float speed);

	Coord GetPos() const;

	bool CanMove(float deltaTime);

	virtual Coord UpdateDirection() const = 0;

	bool Move(const Coord& coord, const Entity* entity);

	virtual ~Moveable();
};

