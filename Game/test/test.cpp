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
	return true;
}

void test::Update()
{
	CVector3 v = p->Getpos();
	v.x += 500;
	v.y += 100;
	sr->SetPosition(v);
}