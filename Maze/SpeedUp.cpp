#include "SpeedUp.h"

char SpeedUp::GetSymbol() const { return '^'; }

int SpeedUp::GetColorCode() const { return 2; }

bool SpeedUp::IsPassable() const { return true; }

void SpeedUp::OnTouch() const{}
