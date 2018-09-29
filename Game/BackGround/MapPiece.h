#pragma once
#include "tkEngine/physics/tkPhysicsStaticObject.h"
#include "BackGround.h"
class MapPiece :public IGameObject
{
public:
	bool Start();
	void Update();
	void init(CVector3 pos, CQuaternion rot,int m);
	void Create();
	void initPhysic();
	void SetPos(CVector3 pos);
	void SetRot(CQuaternion rot);
	prefab::CSkinModelRender* sr;
	CVector3 pos;
	CQuaternion rot;
	int model;
	CPhysicsStaticObject pso;
};