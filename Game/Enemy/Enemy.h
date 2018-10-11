#pragma once
#include "Creature/Creature.h"
class Enemy : public IGameObject,public Creature
{
public:
	bool Start();
	void Update();

	void SetInitPos(CVector3 v)
	{
		inipo = v;
	}
	void Free();
	void Chase();
	void Atack();
	enum Mode
	{
		free,
		chase,
		atack
	};
	void ModeFree()
	{
		mode = free;
	}
	void ModeChase()
	{
		mode = chase;
	}
	void ModeAtack()
	{
		mode = atack;
	}
private:
	CVector3 inipo = CVector3::Zero;
	Mode mode;
	enum anim
	{
		idle,
		walk,
		head,
		anims,
	};
	anim ani = idle;
	CAnimationClip aniclips[anims];
};