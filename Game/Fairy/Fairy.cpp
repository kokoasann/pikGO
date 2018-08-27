#include "stdafx.h"
#include "Fairy.h"

Fairy::~Fairy()
{
}

bool Fairy::Start()
{
	pos.Set(500, 0, 0);
	sr = NewGO < prefab::CSkinModelRender>(0);
	sr->Init(L"modelData/fairy/fairy.cmo", 0, 0, enFbxUpAxisY);
	sr->SetPosition(pos);
	cc.Init(20, 40, pos);
	return true;
}

void Fairy::Update()
{
}
