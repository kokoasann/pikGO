#include "stdafx.h"
#include "Q.h"
#include "BackGround/BackGround.h"

bool Q::Start()
{
	sr = NewGO<prefab::CSkinModelRender>(0);
	sr->Init(L"modelData/map/Q.cmo");
	pos = FindGO<BackGround>("BG")->GetQpos();
	sr->SetPosition(pos);

	pso.CreateMeshObject(sr, pos, CQuaternion::Identity, CVector3::One);
	return true;
}

void Q::Update()
{
}

void Q::SetPos(CVector3 v)
{
	pos = v;
	//sr->SetPosition(pos);
}
