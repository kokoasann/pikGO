#include "stdafx.h"
#include "opChara.h"

opChara::~opChara()
{
	DeleteGO(sr);
}

bool opChara::Start()
{
	return true;
}

void opChara::init(prefab::CSkinModelRender* sr, CVector3 pos)
{
	this->sr = sr;
	this->pos = pos;
	this->sr->SetPosition(pos);
}



bool opChara::Rotation()
{
	CQuaternion ro;
	CVector3 on = oldmove;
	CVector3 om = move;
	on.Normalize();
	om.Normalize();
	float t = on.Dot(om);
	float r = acos(t);
	r /= rotspeed;

	CVector3 ax;
	ax.Cross(on, om);
	ax.Normalize();
	ro.SetRotation(ax, r);
	rot.Multiply(ro);
	
	sr->SetRotation(rot);
	rotcount++;

	return true;
}

void opChara::SetPos(CVector3 pos)
{
	this->pos = pos;
}

void opChara::SetMove(CVector3 v)
{
	oldmove = move;
	move = v;
	Frot = 0.0f;
	rotcount = 0;
	
}

void opChara::SetRot(CQuaternion rot)
{
	this->rot = rot;
}

void opChara::SetRot(float ang)
{
	CQuaternion q;
	q.SetRotationDeg(CVector3::AxisY, ang);
	this->rot = q;
}

void opChara::SetRot(CVector3 v)
{
	CQuaternion q;
	q.SetRotation(CVector3::AxisY, atan2f(v.x, v.z));
	this->rot = q;
}

void opChara::RotaMove()
{
}

void opChara::SetScale(CVector3 v)
{
	sr->SetScale(v);
}

void opChara::playAnim(int num)
{
	sr->PlayAnimation(num);
}

void opChara::Update()
{
	switch (state)
	{
	case idle:
		break;
	case go:
		pos += move;
		sr->SetPosition(pos);
		if (rotcount != rotspeed)
			Rotation();
		break;
	case rota:
		if(rotcount != rotspeed)
			Rotation();
		break;
	}
}