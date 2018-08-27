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
	sr = NewGO<prefab::CSkinModelRender>(0);
	sr->Init(L"modelData/unityChan.cmo");
	cc.Init(10.0f, 10.0f, pos);

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
	speed += vecX * x*200;
	speed += vecZ * z*200;

	pos = cc.Execute(GameTime().GetFrameDeltaTime(), speed);
	sr->SetPosition(pos);

	Rotation();
}