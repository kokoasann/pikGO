#include "stdafx.h"
#include "Pixie.h"
#include "Player.h"
#include "BackGround/RootFind.h"

Pixie::~Pixie()
{
}

bool Pixie::Start()
{
	animClip[anim_idle].Load(L"modelData/pixie/pixie_idle.tka");
	animClip[anim_walk].Load(L"modelData/pixie/pixie_walk.tka");

	animClip[anim_idle].SetLoopFlag(true);
	animClip[anim_walk].SetLoopFlag(true);

	//pos.Set(500, 0, 0);
	//sr = NewGO < prefab::CSkinModelRender>(0);
	//sr->Init(L"modelData/pixie/pixie.cmo",animClip,anim_num);
	//sr->SetPosition(pos);

	//cc.Init(20, 70, pos);

	//sr->PlayAnimation(anim_walk);

	init(inipo, 1.0f, 0.1f, 20.0f, 70.0f,10, L"modelData/pixie/pixie.cmo",animClip,anim_num);
	PlayAnim(anim_idle);
	player = FindGO<Player>("player");
	RF = FindGO<RootFind>("RF");

	CSC.Create(20);

	root = RF->FindRoot(pos, player->Getpos(), piece);
	return true;
}

void Pixie::Update()
{
	Rotation(speed);
	Gravity();
	switch (mode)
	{
	case free:
		Free();
		break;
	case stay:
		Stay();
		break;
	case chase:
		Chase();
		break;
	}
	
}

void Pixie::PushPushed()
{
}

void Pixie::Rotationa(CVector3 v)
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
		//pos = cc.Execute(GameTime().GetFrameDeltaTime(), walk);
		//pos = cc.Execute(GameTime().GetFrameDeltaTime(), speed);

		//sr->SetPosition(pos);

		//Rotation(walk);
		
		Rotation(speed);
		Move();
		if (time > timeUP)
		{
			PlayAnim(anim_idle);
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

			//walk.x = Random().GetRandDouble();
			speed.x = Random().GetRandDouble();

			if (Random().GetRandDouble() <= 0.5)
			{
				//walk.x *= -1;
				speed.x *= -1;

			}
			//walk.z = Random().GetRandDouble();
			speed.z = Random().GetRandDouble();

			if (Random().GetRandDouble() <= 0.5)
			{
				//walk.z *= -1;
				speed.z *= -1;

			}
			//walk *= 200;
			speed.y = 0;
			speed *= 200;

			PlayAnim(anim_walk);
			walking = true;
			time = 0;
		}
	}
}

void Pixie::Stay()
{
	PlayAnim(anim_idle);
}

void Pixie::Chase()
{
	oldpos = pos;
	CVector3 pTp = player->Getpos() - pos;
	if (!(pTp.Length() < 100))
	{
		if (time > 2)
		{
			root = RF->FindRoot(pos, player->Getpos(), piece);
			time = 0;
		}
		if (root.size() != 0)
		{
			speed = root[0] - pos;
			if (speed.Length() > pTp.Length() && root.size() == 1)
				speed = pTp;
			if (speed.Length() < 50.0f)
				root.erase(root.begin());
		}
		else
			speed = pTp;
		speed.Normalize();
		speed *= 500.0f;
		Rotation(speed);
		Move();
	}
	else
		speed = CVector3::Zero;
	time += GameTime().GetFrameDeltaTime();

	CVector3 dif = oldpos - pos;
	if (dif.Length() < 0.1f)
		PlayAnim(anim_idle);
	else
		PlayAnim(anim_walk);
	//speed = player->Getpos() - pos;
	//float t = speed.Length();
	//if (t > 70)
	//{
	//	speed.Normalize();
	//	speed *= 120;
	//	bool hits[7] = { false };
	//	CVector3 hip[7] = { CVector3::Zero };
	//	float ang = 0.0f;
	//	for (int i = 0; i < 7; i++)
	//	{
	//		btTransform start, end;
	//		start.setIdentity();
	//		start.setOrigin(btVector3(pos.x, pos.y, pos.z));
	//		CVector3 nex = pos,sn = speed;
	//		sn.Normalize();

	//		CQuaternion ro;
	//		ro.SetRotationDeg(CVector3::AxisY, ang);
	//		ro.Multiply(sn);
	//		sn *= 120;
	//		nex += sn;

	//		end.setIdentity();
	//		end.setOrigin(btVector3(nex.x, nex.y, nex.z));
	//		RePhy callback;
	//		PhysicsWorld().ConvexSweepTest((const btConvexShape*)CSC.GetBody(), start, end, callback);
	//		hits[i] = callback.isHit;
	//		hip[i] = callback.Hitpo;
	//		
	//		if (i % 2 == 0)
	//		{
	//			ang *= -1;
	//			ang += 30;
	//		}
	//		else
	//		{
	//			ang *= -1.0f;
	//		}
	//	}
	//	CVector3 max = CVector3::Zero;
	//	int num = 0;
	//	for (int i = 0; i < 7; i++)
	//	{
	//		CVector3 dif = pos - hip[i];
	//		CVector3 dim = pos - max;
	//		if (dif.Length() > dim.Length())
	//		{
	//			max = hip[i];
	//			num = i;
	//		}
	//	}
	//	speed = max;
	//	speed.Normalize();
	//	speed *= 100;
	//	//pos = cc.Execute(GameTime().GetFrameDeltaTime(), speed * -100);
	//	//sr->SetPosition(pos);
	//	Rotation(speed);
	//	Move();
	//	if (t > 1500)
	//	{
	//		//mode = stay;
	//	}
	//}
	//else
	//{
	//	speed = CVector3::Zero;
	//}
}
