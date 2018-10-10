#pragma once
#include "tkEngine/character/tkCharacterController.h"
#include "Creature/Creature.h"
class GameCamera;
class BackGround;
class Q;
class Player:public IGameObject,public Creature
{
public:
	Player();
	~Player();
	bool Start() override;
	void Update() override;
	void Rotationa();
	void PikGet();
	void GoalIn();
	void PostRender(CRenderContext& rc) override;

	void SetInitPos(CVector3 v)
	{
		inipo = v;
	}

	CVector3 GetMove()
	{
		return olds - pos;
	}

	bool GetIsClear()
	{
		return isClear;
	}
	//prefab::CSkinModelRender* sr = nullptr;
	//CVector3 pos = CVector3::Zero;
	//CQuaternion rot = CQuaternion::Identity;

	//CCharacterController cc;
	//CVector3 speed = CVector3::Zero;
private:
	CVector3 inipo = CVector3::Zero;
	CSphereCollider collider;
	bool pixG = false;
	bool isGoalDo = false;
	CFont font;
	GameCamera* cam = nullptr;
	int count = 0;

	int pixcount = 0;
	bool isClear = false;

	CVector3 olds = CVector3::Zero;

	BackGround* bg;
	Q* q;
};