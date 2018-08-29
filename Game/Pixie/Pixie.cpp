#include "stdafx.h"
#include "Pixie.h"

Pixie::~Pixie()
{
}

bool Pixie::Start()
{
	animClip[anim_idle].Load(L"modelData/pixie/pixie_idle.tka");
	animClip[anim_walk].Load(L"modelData/pixie/pixie_walk.tka");

	animClip[anim_idle].SetLoopFlag(true);
	animClip[anim_walk].SetLoopFlag(true);

	pos.Set(500, 0, 0);
	sr = NewGO < prefab::CSkinModelRender>(0);
	sr->Init(L"modelData/pixie/pixie.cmo",animClip,anim_num);
	sr->SetPosition(pos);
	cc.Init(20, 70, pos);

	sr->PlayAnimation(anim_walk);
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
