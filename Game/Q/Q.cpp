#include "stdafx.h"
#include "Q.h"

bool Q::Start()
{
	sr = NewGO<prefab::CSkinModelRender>(0);
	sr->Init(L"modelData/map/Q.cmo");
	sr->SetPosition(pos);
	return true;
}

void Q::Update()
{
}
