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
private:
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