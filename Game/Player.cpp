#include "stdafx.h"
#include "Player.h"
#include "Creature/Creature.h"
#include "Pixie/Pixie.h"
#include "Camera/GameCamera.h"

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

	init(pos, 1, 5, 20, 40, L"modelData/unityChan.cmo");
	cam = FindGO<GameCamera>("camera");
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
	if (Pad(0).IsTrigger(enButtonB))
	{
		CVector3 vec = cam->GetPos() - cam->GetTar();
		vec.Normalize();
		QueryGOs<Pixie>("pixie", [&](Pixie* pix)->bool
		{
			CVector3 p = pix->Getpos();
			p.y += 35;
			CVector3 dif = pos - p;
			
			if (dif.Length() < 200)
			{
				CVector3 piv = cam->pos - pix->Getpos();
				piv.Normalize();

				float cta = piv.Dot(vec);
				cta = acosf(cta);
				if (cta < 10)
				{

				}
			}
			return true;
		});
	}
}

void Player::Update()
{
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