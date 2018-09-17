#include "stdafx.h"
#include "PixieSpawner.h"
#include "Pixie.h"

bool PixieSpawner::Start()
{
	int r = 8 + Random().GetRandDouble() * 3;
	for (int c = 0; c < 8; c++)
	{
		int rx = 1 + Random().GetRandDouble() * 27;
		int ry = 1 + Random().GetRandDouble() * 27;

		CVector3 pos = { (float)(rx * 1000),0,(float)(ry * 1000) };
		Pixie* p = NewGO<Pixie>(0,"pixie");
		p->inipo = pos;
		p->Modefree();
	}
	return true;
}
