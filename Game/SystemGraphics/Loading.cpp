#include "stdafx.h"
#include "Loading.h"

Loading::~Loading()
{
	DeleteGO(Rol);
}

bool Loading::Start()
{
	Rol = NewGO < prefab::CSpriteRender>(1);
	Rol->Init(L"sprite/point.dds", 50, 50);
	return true;
}

void Loading::Update()
{
	CQuaternion add;
	add.SetRotationDeg(CVector3::AxisZ,1.0f);
	rot.Multiply(rot, add);
	Rol->SetRotation(rot);
}
