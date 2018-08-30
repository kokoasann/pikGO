#include "stdafx.h"
#include "Pixie.h"
#include "Player.h"

Pixie::~Pixie()
{
}

bool Pixie::Start()
{
	animClip[anim_idle].Load(L"modelData/pixie/pixie_idle.tka");
	animClip[anim_walk].Load(L"modelData/pixie/pixie_walk.tka");

	animClip[anim_idle].SetLoopFlag(true);
	animClip[anim_walk].SetLoopFlag(true);

	pos.Set(500, 0, 0);
	sr = NewGO < prefab::CSkinModelRender>(0);
	sr->Init(L"modelData/pixie/pixie.cmo",animClip,anim_num);
	sr->SetPosition(pos);

	cc.Init(20, 70, pos);

	sr->PlayAnimation(anim_walk);

	player = FindGO<Player>("player");
	return true;
}

void Pixie::Update()
{

	switch (mode)
	{
	case free:
		Free();
		break;
	case stay:
		Stay();
		break;
	case move:
		Move();
		break;
	}
}

void Pixie::PushPushed()
{
}

void Pixie::Rotation(CVector3 v)
{
	if (v.x < 0.0001f && v.z < 0.0001f)
	{
		return;
	}
	float cta = atan2f(-v.x, -v.z);
	rot.SetRotation(CVector3::AxisY, cta);
	sr->SetRotation(rot);
}

void Pixie::Free()
{
	if (walking)
	{
		pos = cc.Execute(GameTime().GetFrameDeltaTime(), walk);
		sr->SetPosition(pos);
		Rotation(walk);
		if (time > timeUP)
		{
			walking = false;
		}
		else
		{
			time += GameTime().GetFrameDeltaTime();
		}
	}
	else
	{
		float rand = Random().GetRandDouble();
		if (rand < 0.001f)
		{
			rand = Random().GetRandDouble();
			timeUP = rand * 2;

			walk.x = Random().GetRandDouble();
			if (Random().GetRandDouble() <= 0.5)
			{
				walk.x *= -1;
			}
			walk.z = Random().GetRandDouble();
			if (Random().GetRandDouble() <= 0.5)
			{
				walk.z *= -1;
			}
			walk *= 200;
			walking = true;
			time = 0;
		}
	}
}

void Pixie::Stay()
{

}

void Pixie::Move()
{
	speed = pos - player->pos;
	float t = speed.Length();
	if (t > 20)
	{
		speed.Normalize();

		pos = cc.Execute(GameTime().GetFrameDeltaTime(), speed * -100);
		sr->SetPosition(pos);
		Rotation(speed);
		if (t > 1500)
		{
			mode = stay;
		}
	}
}
