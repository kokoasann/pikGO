#include "stdafx.h"
#include "PixieSpawner.h"
#include "Pixie.h"

bool PixieSpawner::Start()
{
	
	return true;
}

void PixieSpawner::init(int T, int Y, int RC, int RM)
{
	int r = RC + Random().GetRandDouble() * RM;
	for (int c = 0; c < r; c++)
	{
		int rx = 1 + Random().GetRandDouble() * (T-3);
		int ry = 1 + Random().GetRandDouble() * (Y-3);

		CVector3 pos = { (float)(rx * 1000),0,(float)(ry * 1000) };
		Pixie* p = NewGO<Pixie>(0, "pixie");
		p->SetInitPos(pos);
		//p->Modechase();
	}
	DeleteGO(this);
}

void PixieSpawner::TestSpawn()
{
	CVector3 pos = { (float)(1 * 1000),0,(float)(1 * 1000) };
	Pixie* p = NewGO<Pixie>(0, "pixie");
	p->SetInitPos(pos);
	p->Modechase();
	DeleteGO(this);
}
