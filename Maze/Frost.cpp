#include "Frost.h"

char Frost::GetSymbol() const { return 'F'; }

int Frost::GetColorCode() const { return 6; }

bool Frost::IsPassable() const { return true; }

void Frost::OnTouch() const
{
}
