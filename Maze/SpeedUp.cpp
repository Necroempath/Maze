#include "SpeedUp.h"

char SpeedUp::GetSymbol() const { return '^'; }

int SpeedUp::GetColorCode() const { return 2; }

void SpeedUp::OnTouch(GameData& data) const
{
	data.player->SetSpeed(20);
	data.speedUpTime = 20;
}
