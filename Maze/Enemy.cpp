#include "Enemy.h"

Enemy::Enemy(const Coord& position, float speed) : Moveable(position, speed) {}

char Enemy::GetSymbol() const { return '!'; }

int Enemy::GetColorCode() const { return 4; }

bool Enemy::IsPassable() const { return false; }

Coord Enemy::UpdateDirection() const { return Coord(); }