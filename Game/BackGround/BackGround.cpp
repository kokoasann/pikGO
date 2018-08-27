#include "stdafx.h"
#include "BackGround.h"

BackGround::~BackGround()
{
}

bool BackGround::Start()
{
	mainMap = NewGO<prefab::CSkinModelRender>(0);
	mainMap->Init(L"modelData/map/tesmap.cmo",0,0,enFbxUpAxisY);
	mainMap->SetPosition({ 0,0,0 });
	mainMap->SetScale({ 0.5f,0.5f,0.5f });
	return true;
}

void BackGround::Update()
{
}
