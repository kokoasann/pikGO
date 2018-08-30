#pragma once
#include <stdafx.h>
class Creature;
class CreatureManager:public IGameObject
{
public:
	void add(Creature* C);
	void Creatures(std::function<void(Creature* crea)> fnc);
	std::list<Creature*> creatureList;
};