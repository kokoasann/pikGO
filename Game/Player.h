#pragma once
#include "tkEngine/character/tkCharacterController.h"
class GameCamera;
class Player:public IGameObject
{
public:
	Player();
	~Player();
	bool Start() override;
	void Update() override;
	void Rotation();
	void PikGet();

	prefab::CSkinModelRender* sr = nullptr;
	CVector3 pos = CVector3::Zero;
	CQuaternion rot = CQuaternion::Identity;

	CCharacterController cc;
	CVector3 speed = CVector3::Zero;
	CVector3 olds = CVector3::Zero;

	GameCamera* cam = nullptr;
	int count = 0;
	CVector3 GetMove()
	{
		return pos - olds;
	}
};