#include "stdafx.h"
#include "CreatureManager.h"
#include "Creature.h"
void CreatureManager::add(Creature* C)
{
	creatureList.push_back(C);
}

void CreatureManager::Creatures(std::function<void(Creature* crea)> fnc)
{
	for (Creature* creature : creatureList)
	{
		fnc(creature);
	}
}
