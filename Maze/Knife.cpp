#include "Knife.h"

char Knife::GetSymbol() const { return 'X'; }

int Knife::GetColorCode() const { return 13; }

bool Knife::IsPassable() const { return true; }

void Knife::OnTouch() const
{
}
