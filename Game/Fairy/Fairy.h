#pragma once
#include "tkEngine/character/tkCharacterController.h"
class Fairy:public IGameObject
{
public:
	~Fairy();
	bool Start() override;
	void Update() override;

	prefab::CSkinModelRender* sr = nullptr;

	CVector3 pos = CVector3::Zero;
	
	CCharacterController cc;
};

