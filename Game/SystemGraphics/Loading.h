#pragma once

class Loading :public IGameObject
{
public:
	~Loading();
	bool Start() override;
	void Update() override;

	prefab::CSpriteRender* Rol = nullptr;
	CVector3 pos;
	CQuaternion rot = CQuaternion::Identity;
};