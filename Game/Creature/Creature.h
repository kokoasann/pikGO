#pragma once
#include "CreatureManager.h"
#include "tkEngine/character/tkCharacterController.h"
class Creature:Noncopyable
{
public:
	void init(CVector3 pos,float scale, float weight, float radius, float height, const wchar_t*modelpath, CAnimationClip* anim = nullptr,int clips = 0);
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

	float Getweight()
	{
		return weight;
	}
	float Getradius()
	{
		return radius;
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

	float grav = 1500;

	CCharacterController cc;
	float radius;
	float height;

	prefab::CSkinModelRender* sr;

	CreatureManager* creatureManager;
};