#include "stdafx.h"
#include "Enemy.h"

bool Enemy::Start()
{
	aniclips[idle].Load(L"modelData/mamono/mamono_anim.tka");
	aniclips[walk].Load(L"modelData/mamono/mamono_walk.tka");
	//aniclips[walk].Load(L"modelData/mamono/anime.tka");
	aniclips[head].Load(L"modelData/mamono/mamono_hed.tka");
	aniclips[idle].SetLoopFlag(true);
	aniclips[walk].SetLoopFlag(true);
	init(inipo, 10.0f, 10.0f, 50.0f, 70.0f, 50, L"modelData/mamono/mamono.2.cmo",aniclips,anims );

	PlayAnim(walk);
	return true;
}

void Enemy::Update()
{

}
