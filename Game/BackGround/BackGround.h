#pragma once

class BackGround :public IGameObject
{
public:
	~BackGround();
	bool Start() override;
	void Update() override;

	prefab::CSkinModelRender* mainMap = nullptr;
};