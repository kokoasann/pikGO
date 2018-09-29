#include "stdafx.h"
#include "Enemy.h"

bool Enemy::Start()
{
	aniclips[idle].Load(L"modelData/mamono/mamono_anim.tka");
	aniclips[walk].Load(L"modelData/mamono/mamono_walk.tka");
	aniclips[head].Load(L"modelData/mamono/mamono_hed.tka");
	aniclips[idle].SetLoopFlag(true);
	aniclips[walk].SetLoopFlag(true);
	init(inipo, 0.5f, 10.0f, 50.0f, 70.0f, 50, L"modelData/mamono/mamono.cmo",aniclips,anims );

	PlayAnim(idle);
	return true;
}

void Enemy::Update()
{

}
