#pragma once
#include "Creature/Creature.h"
class EnemySpawner : public IGameObject, public Creature
{
public:
	bool Start();
	void Update();
	void init(int T, int Y,int RC,int RM);
};