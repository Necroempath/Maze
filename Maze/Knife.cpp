#include "Knife.h"

char Knife::GetSymbol() const { return 'X'; }

int Knife::GetColorCode() const { return 13; }

void Knife::OnTouch(GameData& data)
{
	data.knifeActive = true;
	data.knifeActivationTime = 20;

	_isActive = false;
}
