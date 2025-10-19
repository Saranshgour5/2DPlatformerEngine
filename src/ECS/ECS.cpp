#include "ECS.h"

void ECS::Entity::addGroup(Group mGroup) noexcept
{
	groupBitset[mGroup] = true;
	manager.addToGroup(this, mGroup);
}

