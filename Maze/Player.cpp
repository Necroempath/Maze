#include "Player.h"

Player::Player(const Coord& postition, float speed, short health) : Moveable(postition, speed), _health(health) {}

char Player::GetSymbol() const { return '@'; }

int Player::GetColorCode() const { return 1; }

bool Player::IsPassable() const { return false; }

Coord Player::UpdateDirection() const { return _position + ConsoleUI::GetDirection(); }
