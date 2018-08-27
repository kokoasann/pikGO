#include "stdafx.h"
#include "Player.h"
#include "Camera/GameCamera.h"

Player::Player()
{
}


Player::~Player()
{
}

bool Player::Start()
{
	pos.Set(0, 10, 0);
	sr = NewGO<prefab::CSkinModelRender>(0);
	sr->Init(L"modelData/unityChan.cmo");
	cc.Init(20.0f, 40.0f, pos);

	cam = FindGO<GameCamera>("camera");
	return true;
}

void Player::Rotation()
{
	if (fabsf(speed.x) <= 0.0001f && fabsf(speed.z) <= 0.0001f)
	{
		return;
	}
	float ang = atan2(speed.x, speed.z);

	rot.SetRotation(CVector3::AxisY, ang);

	sr->SetRotation(rot);
}

void Player::Update()
{
	olds = pos;

	CVector3 vecX = cam->GetPos() - cam->GetTar();
	vecX.y = 0;
	vecX.Normalize();

	CVector3 vecZ = vecX;
	vecZ.Cross(CVector3::AxisY);
	vecZ.Normalize();

	float x = Pad(0).GetLStickYF()*-1.0f;
	float z = Pad(0).GetLStickXF();

	speed.x = 0;
	speed.z = 0;
	speed += vecX * x*300;
	speed += vecZ * z*300;

	if (Pad(0).IsTrigger(enButtonA) && cc.IsOnGround())
	{
		speed.y += 400;
	}
	speed.y -= 500*GameTime().GetFrameDeltaTime();

	pos = cc.Execute(GameTime().GetFrameDeltaTime(), speed);

	if (cc.IsOnGround())
	{
		speed.y = 0;
	}


	sr->SetPosition(pos);
	
	


	Rotation();
}