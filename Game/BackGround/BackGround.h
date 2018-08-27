#pragma once
#include "tkEngine/physics/tkPhysicsStaticObject.h"
class BackGround :public IGameObject
{
public:
	~BackGround();
	bool Start() override;
	void Update() override;

	prefab::CSkinModelRender* mainMap = nullptr;
	CPhysicsStaticObject pso;
};