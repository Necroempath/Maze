#include "Frost.h"

char Frost::GetSymbol() const { return 'F'; }

int Frost::GetColorCode() const { return 6; }

void Frost::OnTouch(GameData& data) const
{
	data.enemiesFrozen = true;
	data.freezeTime = 15;
}
