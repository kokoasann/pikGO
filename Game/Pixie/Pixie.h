#pragma once
#include "tkEngine/character/tkCharacterController.h"
class Pixie:public IGameObject
{
public:
	~Pixie();
	bool Start() override;
	void Update() override;

	prefab::CSkinModelRender* sr = nullptr;

	CVector3 pos = CVector3::Zero;
	
	CCharacterController cc;

	bool ac = false;

	enum AnimationClip
	{
		anim_idle,
		anim_walk,
		anim_num
	};
	CAnimationClip animClip[anim_num];
};

