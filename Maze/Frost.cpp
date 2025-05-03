#include "Frost.h"

char Frost::GetSymbol() const { return 'F'; }

int Frost::GetColorCode() const { return 6; }

void Frost::OnTouch(GameData& data)
{
	data.enemiesFrozen = true;
	data.freezeTime = 15;

	_isActive = false;
}
