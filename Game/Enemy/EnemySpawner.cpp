#include "stdafx.h"
#include "Enemy.h"
#include "EnemySpawner.h"

bool EnemySpawner::Start()
{
	
	return true;
}

void EnemySpawner::Update()
{
}

void EnemySpawner::init(int T, int Y,int RC,int RM)
{
	int r = RC + Random().GetRandDouble() * RM;
	for (int c = 0; c < r; c++)
	{
		int rx = 1 + Random().GetRandDouble() * (T-3);
		int ry = 1 + Random().GetRandDouble() * (Y-3);

		CVector3 pos = { (float)(rx * 1000),0,(float)(ry * 1000) };
		Enemy* e = NewGO<Enemy>(0, "enemy");
		e->SetInitPos(pos);
	}
}
