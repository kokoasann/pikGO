#include "stdafx.h"
#include "Pixie.h"

Pixie::~Pixie()
{
}

bool Pixie::Start()
{
	pos.Set(500, 0, 0);
	sr = NewGO < prefab::CSkinModelRender>(0);
	sr->Init(L"modelData/pixie/pixie.cmo");
	sr->SetPosition(pos);
	cc.Init(20, 70, pos);
	return true;
}

void Pixie::Update()
{
	if (ac)
	{
		pos.y += 20;
		sr->SetPosition(pos);
	}
}
