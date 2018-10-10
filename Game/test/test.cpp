#include "stdafx.h"
#include "test.h"
#include "Player.h"
bool test::Start()
{
	anim.Load(L"modelData/tes/anime.tka");
	anim.SetLoopFlag(true);
	sr = NewGO < prefab::CSkinModelRender>(0);
	sr->Init(L"modelData/tes/bone.cmo", &anim, 1);
	sr->PlayAnimation(0);
	p = FindGO<Player>("player");
	sr->SetPosition(CVector3::Zero);
	return true;
}

void test::Update()
{
	/*CVector3 v = p->Getpos();
	v.x += 500;
	v.y += 100;
	sr->SetPosition(v);*/

	//CVector3 PL = CVector3::Zero;
	PL.y = 500;
	PL.z = (p->Getpos().z / 1000.0f / 1.0f/3.0f) + 1;
	PL.x = (p->Getpos().x / 1000.0f / 1.0f / 3.0f) + 1;
	
	PL.z = (p->Getpos().z-1 * 1000.0f * 1.0f / 3.0f);
	PL.x = (p->Getpos().x-1 * 1000.0f * 1.0f / 3.0f);
	sr->SetPosition(PL);
}