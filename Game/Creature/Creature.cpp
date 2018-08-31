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
		if (crea != this)
		{
			CVector3 diff = pos - crea->Getpos();
			diff.y = 0;
			if (diff.Length() <= radius + crea->Getradius()+5)
			{
				if (weight >= crea->Getweight())
				{
					float f = (weight - crea->Getweight()) / (weight + crea->Getweight());
					speed -= speed * f;
					CVector3 v = speed;

					diff.Normalize();
					
					crea->PullOtherSpeed(diff * f *150);
					crea->OtherMove();
				}
			}
		}
		return;
	});
	pos = cc.Execute(GameTime().GetFrameDeltaTime(), speed);

	if (cc.IsOnGround())
	{
		speed.y = 0;
	}

	sr->SetPosition(pos);
}

void Creature::OtherMove()
{
	pos = cc.Execute(GameTime().GetFrameDeltaTime(), otherspeed);
	sr->SetPosition(pos);
	otherspeed = CVector3::Zero;
}

void Creature::Gravity()
{
	speed.y -= grav * GameTime().GetFrameDeltaTime();

}

void Creature::PushPushed()
{

}

void Creature::PlayAnim(int anm)
{
	sr->PlayAnimation(anm);
}
