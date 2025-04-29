#include "Moveable.h"

Coord Moveable::GetPos() const { return _position; }

bool Moveable::CanMove(float deltaTime)
{
	_timeSinceLastMove += deltaTime;

	if (_timeSinceLastMove >= 1.0f / _speed)
	{
		_timeSinceLastMove = 0.0f;
		return true;
	}
	return false;
}

bool Moveable::Move(const Coord& coord, const Entity* entity)
{
	if (entity->IsPassable())
	{
		_position = coord;

		return true;		
	}

	return false;
}

Moveable::~Moveable() = default;
