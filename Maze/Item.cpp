#include "Item.h"

bool Item::IsPassable() const { return true; }

bool Item::IsActive() const { return _isActive; }

Item::~Item() = default;

