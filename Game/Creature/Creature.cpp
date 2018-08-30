#include "stdafx.h"
#include "Creature.h"
#include "CreatureManager.h"

void Creature::init(CVector3 pos,float scale, float weight, float radius, float height, const wchar_t * modelpath, CAnimationClip* anim, int clips)
{
	this->pos = pos;
	this->weight = weight;
	this->radius = radius;
	this->height = height;
	sr = NewGO < prefab::CSkinModelRender>(0);
	if (anim == nullptr)
		sr->Init(modelpath);
	else
	{
		sr->Init(modelpath, anim, clips);
	}
	sr->SetPosition(pos);
	sr->SetScale(CVector3::One*scale);
	cc.Init(radius, height, this->pos);

	creatureManager = FindGO<CreatureManager>("CM");
	creatureManager->add(this);

}

void Creature::Rotation(CVector3 v)
{
	if (fabsf(v.x) < 0.0001 && fabsf(v.z) < 0.0001)
	{
		return;
	}
	float cta = atan2f(v.x, v.z);
	rot.SetRotation(CVector3::AxisY, cta);
	sr->SetRotation(rot);
}

void Creature::Move()
{
	creatureManager->Creatures([&](Creature* crea)->void 
	{
		CVector3 diff = pos - crea->Getpos();
		if (diff.Length() < radius + crea->Getradius())
		{
			if (weight >= crea->Getweight())
			{
				speed -= speed * (weight - crea->Getweight())/(weight + crea->Getweight());
				CVector3 v = speed;
				diff.Normalize();
				crea->Addspeed(diff * 20);
				crea->Move();
			}
		}
		return;
	});
	pos = cc.Execute(GameTime().GetFrameDeltaTime(), speed);
	sr->SetPosition(pos);
}

void Creature::PushPushed()
{

}

void Creature::PlayAnim(int anm)
{
	sr->PlayAnimation(anm);
}
