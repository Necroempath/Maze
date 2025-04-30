#include "Player.h"
#include <conio.h>

Player::Player(const Coord& postition, float speed, short health) : Moveable(postition, speed), _health(health) {}

char Player::GetSymbol() const { return '@'; }

int Player::GetColorCode() const { return 1; }

bool Player::IsPassable() const { return false; }

short Player::GetHealth() const { return _health; }

void Player::SetHealth(short health) { _health = health; }

Coord Player::UpdateDirection() const { return _position + GetDirection(); }

Coord Player::GetDirection() const
{

	if (_kbhit())
	{
		char input = _getch();

		switch (input)
		{
		case 'w': return Coord(-1, 0);
			break;
		case 's': return Coord(1, 0);
			break;
		case 'a': return Coord(0, -1);
			break;
		case 'd': return Coord(0, 1);
			break;
		}
	}

	return Coord();
}
