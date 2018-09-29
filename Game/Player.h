#pragma once
#include "tkEngine/character/tkCharacterController.h"
#include "Creature/Creature.h"
class GameCamera;
class BackGround;
class Player:public IGameObject,public Creature
{
public:
	Player();
	~Player();
	bool Start() override;
	void Update() override;
	void Rotationa();
	void PikGet();
	void PostRender(CRenderContext& rc) override;

	//prefab::CSkinModelRender* sr = nullptr;
	//CVector3 pos = CVector3::Zero;
	//CQuaternion rot = CQuaternion::Identity;

	//CCharacterController cc;
	//CVector3 speed = CVector3::Zero;
	CVector3 inipo = CVector3::Zero;
	CSphereCollider collider;
	bool pixG = false;
	CFont font;
	GameCamera* cam = nullptr;
	int count = 0;

	CVector3 olds = CVector3::Zero;

	BackGround* bg;
	CVector3 GetMove()
	{
		return olds - pos;
	}
};