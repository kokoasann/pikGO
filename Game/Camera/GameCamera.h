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
	CVector3 tar = CVector3::Zero;
	CVector3 toto = CVector3::Zero;
	CVector3 tota = CVector3::Zero;
	CSpringCamera Scamera;
	CCamera* camera;
	CCameraCollisionSolver CCS;
	Player* player = nullptr;

	CVector3 GetPos()
	{
		//return Scamera.GetPosition();
		return MainCamera().GetPosition();
	}
	CVector3 GetTar()
	{
		//return Scamera.GetTarget();
		return MainCamera().GetTarget();
	}
};