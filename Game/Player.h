#pragma once
class Player:public IGameObject
{
public:
	Player();
	~Player();
	bool Start() override;
	void Update() override;

	prefab::CSkinmodelRender* sr = nullptr;
	CVector3 pos = CVector3::Zeros;
};

