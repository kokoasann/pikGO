#include "stdafx.h"
#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
}

bool Player::Start()
{
	sr->Init(L"modelData/unityChan.cmo");
	cc.Init(10.0f, 10.0f, pos);

	return true;
}

void Player::Update()
{

}