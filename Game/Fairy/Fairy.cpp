#include "stdafx.h"
#include "Fairy.h"

Fairy::~Fairy()
{
}

bool Fairy::Start()
{
	pos.Set(50, 0, 0);
	sr = NewGO < prefab::CSkinModelRender>(0);
	sr->Init(L"modelData/fairy/fairy.cmo", 0, 0, enFbxUpAxisY);
	cc.Init(10, 10, pos);
	return true;
}

void Fairy::Update()
{
}
