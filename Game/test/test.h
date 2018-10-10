#pragma once
class Player;
class test :public IGameObject
{
public:
	bool Start();
	void Update();
	prefab::CSkinModelRender* sr = nullptr;
	CAnimationClip anim;
	Player* p;

	CVector3 PL = CVector3::Zero;
};