#include "stdafx.h"
#include "Player.h"
#include "Creature/Creature.h"
#include "Pixie/Pixie.h"
#include "Camera/GameCamera.h"
#include "BackGround/BackGround.h"

Player::Player()
{
}


Player::~Player()
{
}

bool Player::Start()
{
	//pos.Set(15000, 5500, 15000);
	//sr = NewGO<prefab::CSkinModelRender>(0);
	//sr->Init(L"modelData/unityChan.cmo");
	//cc.Init(20.0f, 40.0f, pos);

	init(inipo, 1.0f, 5.0f, 20.0f, 40.0f,30, L"modelData/unityChan.cmo");
	cam = FindGO<GameCamera>("camera");
	collider.Create(0.5f);
	bg = FindGO<BackGround>("BG");
	return true;
}

void Player::Rotationa()
{
	if (fabsf(speed.x) <= 0.0001f && fabsf(speed.z) <= 0.0001f)
	{
		return;
	}
	float ang = atan2(speed.x, speed.z);

	rot.SetRotation(CVector3::AxisY, ang);

	sr->SetRotation(rot);
}

void Player::PikGet()
{
	CVector3 cap = cam->GetPos();
	CVector3 cat = cam->GetTar();
	CVector3 vec = cap - cat;
	
	vec.Normalize();
	QueryGOs<Pixie>("pixie", [&](Pixie* pix)->bool
	{
		if (pix->mode == Pixie::Mode::free)
		{
		}
		CVector3 p = pix->Getpos();
		p.y += 35;
		CVector3 dif = pos - p;

		if (dif.Length() < 200)
		{
			btTransform btStart, btEnd;
			btStart.setIdentity();
			btEnd.setIdentity();

			btStart.setOrigin(btVector3(cap.x, cap.y, cap.z));
			btEnd.setOrigin(btVector3(cat.x, cat.y, cat.z));
			collback callback(vec);
			//	callback.m_collisionFilterGroup = 
			PhysicsWorld().ConvexSweepTest((const btConvexShape*)collider.GetBody(), btStart, btEnd, callback);
			if (callback.hasHit())
			{
				pixG = true;
				if (Pad(0).IsTrigger(enButtonB))
				{
					pix->Modechase();
				}
			}
			/*CVector3 piv = cam->pos - pix->Getpos();
			piv.Normalize();

			float cta = piv.Dot(vec);
			cta = acosf(cta);
			if (cta < 10.0f/CMath::PI*180.0f)
			{
				
			}
			else
			{
				pixG = false;
			}*/
		}
		return true;
	});
}

void Player::Update()
{
	if (!bg->iniend)
	{
		return;
	}
	CVector3 vecX = cam->GetPos() - cam->GetTar();
	vecX.y = 0;
	vecX.Normalize();

	CVector3 vecZ = vecX;
	vecZ.Cross(CVector3::AxisY);
	vecZ.Normalize();

	float x = Pad(0).GetLStickYF()*-1.0f;
	float z = Pad(0).GetLStickXF();
	//z = Pad(0).GetWheel();

	speed.x = 0;
	speed.z = 0;
	speed += vecX * x*1000;
	speed += vecZ * z*1000;

	if (fabsf(speed.x) <= 0.0001f && fabsf(speed.z) <= 0.0001f)
		olds = Getpos();
	if (Pad(0).IsTrigger(enButtonA)&& cc.IsOnGround())
	{
		speed.y += 400;
	}
	//speed.y -= 500*GameTime().GetFrameDeltaTime();

	//Setspeed(speed);

	//pos = cc.Execute(GameTime().GetFrameDeltaTime(), speed);

	//if (cc.IsOnGround())
	//{
	//	speed.y = 0;
	//	//Setspeed(speed);
	//}


	//sr->SetPosition(pos);

	
	Rotation(speed);
	Gravity();
	Move();
	PikGet();
}

void Player::PostRender(CRenderContext & rc)
{
	if (pixG)
	{
		font.Begin(rc);
		font.Draw(L"E ’‡ŠÔ‚É‚·‚é", { 0,-10},CVector4::White,0,0.5f);
		font.End(rc);
		pixG = false;
	}
}