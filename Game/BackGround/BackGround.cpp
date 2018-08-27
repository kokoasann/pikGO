#include "stdafx.h"
#include "BackGround.h"

BackGround::~BackGround()
{
}

bool BackGround::Start()
{
	mainMap = NewGO<prefab::CSkinModelRender>(0);
	mainMap->Init(L"modelData/map/tesmap.cmo");
	//mainMap->SetPosition({ 0,0,0 });
	//mainMap->SetScale({ 0.5f,0.5f,0.5f });

	pso.CreateMeshObject(mainMap, CVector3::Zero, CQuaternion::Identity, CVector3::One);
	return true;
}

void BackGround::Update()
{
}
