#pragma once
#include "tkEngine/character/tkCharacterController.h"
class Player:public IGameObject
{
public:
	Player();
	~Player();
	bool Start() override;
	void Update() override;

	prefab::CSkinModelRender* sr = nullptr;
	CVector3 pos = CVector3::Zero;
	CQuaternion rot = CQuaternion::Identity;

	CCharacterController cc;
	CVector3 speed = CVector3::Zero;
};