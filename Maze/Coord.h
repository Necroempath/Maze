#pragma once

class Coord
{
private:
    short _y, _x;

public:
    Coord();
    Coord(short y, short x);

    short GetY() const;
    short GetX() const;

    void SetY(short y);
    void SetX(short x);

    Coord operator+(const Coord& other) const;
    Coord operator-(const Coord& other) const;

    Coord& operator+=(const Coord& other);
    Coord& operator-=(const Coord& other);

    bool operator==(const Coord& other) const;
    bool operator!=(const Coord& other) const;
};
