#pragma once

class Q :public IGameObject
{
public:
	bool Start();
	void Update();

	prefab::CSkinModelRender* sr;
	CVector3 pos = CVector3::Zero;
};