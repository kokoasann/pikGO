#include "stdafx.h"
#include "CreatureManager.h"
#include "Creature.h"
bool CreatureManager::Start()
{
	return true;
}
void CreatureManager::add(Creature* C)
{
	creatureList.push_back(C);
}

void CreatureManager::deleteC(Creature * C)
{
	std::list<Creature*>::iterator it = std::find(creatureList.begin(), creatureList.end(), C);
	creatureList.erase(it);
}

void CreatureManager::Creatures(std::function<void(Creature* crea)> fnc)
{
	for (Creature* creature : creatureList)
	{
		fnc(creature);
	}
}
