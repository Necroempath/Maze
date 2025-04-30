#include "Key.h"

char Key::GetSymbol() const { return 'k'; }

int Key::GetColorCode() const { return 13; }

void Key::OnTouch(GameData& data) const 
{
	data.keysObtained++;
};

