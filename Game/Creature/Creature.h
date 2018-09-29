#pragma once
#include "CreatureManager.h"
#include "tkEngine/character/tkCharacterController.h"

struct collback :public btCollisionWorld::ClosestConvexResultCallback
{
public:
	CVector3 hitNor;
	CVector3 hitPoi;
	CVector3 m_rayDir;
	btCollisionObject* hitObj;
	btCollisionObject* me = nullptr;
	collback(CVector3 rayDir) :
		btCollisionWorld::ClosestConvexResultCallback(btVector3(0.0f, 0.0f, 0.0f), btVector3(0.0f, 0.0f, 0.0f)),
		m_rayDir(rayDir) {}
	virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		hitNor = *(CVector3*)&convexResult.m_hitNormalLocal;
		hitPoi = *(CVector3*)&convexResult.m_hitPointLocal;
		hitObj = (btCollisionObject*)& convexResult.m_hitCollisionObject;
		CVector3 normal;
		normal.Set(convexResult.m_hitNormalLocal);

		if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Character) {
			//return 1.0f;
		}
		return btCollisionWorld::ClosestConvexResultCallback::addSingleResult(convexResult, normalInWorldSpace);
	}
};

class Creature:Noncopyable
{
public:
	void init(CVector3 pos,float scale, float weight, float radius, float height,int hp, const wchar_t*modelpath, CAnimationClip* anim = nullptr,int clips = 0);
	void Rotation(CVector3 v);
	
	void Move();
	void OtherMove();
	void Gravity();
	void PushPushed();
	CVector3 Getpos()
	{
		return pos;
	}
	void Setpos(CVector3 v);
	
	CVector3 Addpos(CVector3 v)
	{
		pos += v;
		return pos;
	}
	CVector3 Pullpos(CVector3 v)
	{
		pos -= v;
		return pos;
	}
	
	CVector3 Getspeed()
	{
		return speed;
	}
	void Setspeed(CVector3 v)
	{
		speed = v;
	}
	CVector3 Addspeed(CVector3 v)
	{
		speed += v;
		return speed;
	}
	CVector3 Pullspeed(CVector3 v)
	{
		speed -= v;
		return speed;
	}

	CVector3 GetOtherSpeed()
	{
		return otherspeed;
	}
	void SetOtherSpeed(CVector3 v)
	{
		otherspeed = v;
	}
	CVector3 AddOtherSpeed(CVector3 v)
	{
		otherspeed += v;
		return otherspeed;
	}
	CVector3 PullOtherSpeed(CVector3 v)
	{
		otherspeed -= v;
		return otherspeed;
	}
	CCharacterController* GetCollider()
	{
		return &cc;
	}
	float Getweight()
	{
		return weight;
	}
	float Getradius()
	{
		return radius;
	}

	int GetHP()
	{
		return HP;
	}
	void SetHP(int p)
	{
		HP = p;
	}

	void PlayAnim(int anm);

	Creature* GetCreature()
	{
		return this;
	}
protected:
	CVector3 pos;
	CVector3 speed;
	CVector3 otherspeed;
	CQuaternion rot;
	float weight;

	int HP;

	float grav = 1500;

	CCharacterController cc;
	float radius;
	float height;

	prefab::CSkinModelRender* sr;

	CreatureManager* creatureManager;
};