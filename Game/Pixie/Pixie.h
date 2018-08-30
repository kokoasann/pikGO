#pragma once
#include "tkEngine/character/tkCharacterController.h"
#include "Creature/Creature.h"
class Player;
class Pixie:public IGameObject,public Creature
{
public:
	~Pixie();
	bool Start() override;
	void Update() override;
	
	void PushPushed();
	void Rotation(CVector3 v);

	void Free();
	void Stay();
	void Move();

	prefab::CSkinModelRender* sr = nullptr;

	CVector3 pos = CVector3::Zero;
	CQuaternion rot = CQuaternion::Identity;
	CVector3 speed = CVector3::Zero;
	
	CCharacterController cc;
	float weight = 0.5f;

	bool walking = false;
	CVector3 walk = CVector3::Zero;
	float time = 0;
	float timeUP = 0;

	Player* player = nullptr;

	enum Mode
	{
		free,
		stay,
		move
	};

	Mode mode = free;

	enum AnimationClip
	{
		anim_idle,
		anim_walk,
		anim_num
	};
	CAnimationClip animClip[anim_num];
};

