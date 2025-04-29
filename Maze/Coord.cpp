#include "Coord.h"

Coord::Coord() : _y(0), _x(0) {}

Coord::Coord(short y, short x) : _y(y), _x(x) {}

short Coord::GetY() const { return _y; }
short Coord::GetX() const { return _x; }

void Coord::SetY(short y) { _y = y; }
void Coord::SetX(short x) { _x = x; }

Coord Coord::operator+(const Coord& other) const {
    return Coord(_y + other._y, _x + other._x);
}

Coord Coord::operator-(const Coord& other) const {
    return Coord(_y - other._y, _x - other._x);
}

Coord& Coord::operator+=(const Coord& other) {
    _y += other._y;
    _x += other._x;
    return *this;
}

Coord& Coord::operator-=(const Coord& other) {
    _y -= other._y;
    _x -= other._x;
    return *this;
}

bool Coord::operator==(const Coord& other) const {
    return _y == other._y && _x == other._x;
}

bool Coord::operator!=(const Coord& other) const {
    return _y != other._y || _x != other._x;
}
