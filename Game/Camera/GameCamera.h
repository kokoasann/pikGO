#pragma once
#include "tkEngine/camera/tkSpringCamera.h"
class Player;
class GameCamera:public IGameObject
{
public:
	~GameCamera();

	bool Start() override;
	void Update() override;

	CVector3 pos = CVector3::Zero;
	CSpringCamera Scamera;

	Player* player = nullptr;
};