#pragma once
#include "tkEngine/character/tkCharacterController.h"
#include "Creature/Creature.h"
#include "tkEngine/Physics/tkSphereCollider.h"
#include "BackGround/RootFind.h"

struct RePhy : public btCollisionWorld::ConvexResultCallback
{
	bool isHit = false;
	CVector3 Hitpo = CVector3::Zero;
	virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		isHit = true;
		Hitpo = *(CVector3*)&convexResult.m_hitPointLocal;
		return 0.0f;
	}
};
class RootFind;
class Player;
class Pixie:public IGameObject,public Creature
{
public:
	~Pixie();
	bool Start() override;
	void Update() override;
	
	void PushPushed();
	void Rotationa(CVector3 v);

	void SetInitPos(CVector3 v)
	{
		inipo = v;
	}

	enum Mode
	{
		free,
		stay,
		chase
	};

	void Free();
	void Stay();
	void Chase();

	void Modefree()
	{
		mode = free;
	}
	void Modestay()
	{
		mode = stay;
	}
	void Modechase()
	{
		mode = chase;
	}
	
	Piece GetPiece()
	{
		return piece;
	}

	Mode GetMode()
	{
		return mode;
	}

private:
	//prefab::CSkinModelRender* sr = nullptr;

	//CVector3 pos = CVector3::Zero;
	//CQuaternion rot = CQuaternion::Identity;
	//CVector3 speed = CVector3::Zero;
	
	//CCharacterController cc;
	//float weight = 0.5f;

	bool walking = false;
	//CVector3 walk = CVector3::Zero;
	float time = 0;
	float timeUP = 0;
	CVector3 inipo = CVector3::Zero;
	Player* player = nullptr;
	RootFind* RF = nullptr;
	Piece piece;

	CSphereCollider CSC;

	

	Mode mode = stay;

	//float time = 0.0f;
	std::vector<CVector3> root;

	enum AnimationClip
	{
		anim_idle,
		anim_walk,
		anim_num
	};
	CAnimationClip animClip[anim_num];
};

