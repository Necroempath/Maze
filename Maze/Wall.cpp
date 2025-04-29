#include "Wall.h"

char Wall::GetSymbol() const { return '#'; }

int Wall::GetColorCode() const { return 7; }

bool Wall::IsPassable() const { return false; }
