#pragma once
#include "Creature/Creature.h"
class Enemy : public IGameObject,public Creature
{
public:
	bool Start();
	void Update();

	CVector3 inipo = CVector3::Zero;
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