#pragma once
#include "tkEngine/physics/tkPhysicsStaticObject.h"
class BackGround :public IGameObject
{
public:
	~BackGround();
	bool Start() override;
	void Update() override;

	int map[30][30] = {0};
	
	prefab::CSkinModelRender* start = nullptr;
	prefab::CSkinModelRender* end = nullptr;
	std::list<prefab::CSkinModelRender*> maps;

	std::vector<CPhysicsStaticObject> psolist;
	CPhysicsStaticObject psoa[900];
	//CPhysicsStaticObject pso,pso2;
};