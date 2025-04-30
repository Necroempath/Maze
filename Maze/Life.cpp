#include "Life.h"

char Life::GetSymbol() const { return '$'; }

int Life::GetColorCode() const { return 3; }

void Life::OnTouch(GameData& data) const
{
	data.player->SetHealth(data.player->GetHealth() + 1);
}
