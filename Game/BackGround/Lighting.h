#pragma once

class Lighting :public IGameObject
{
public:
	~Lighting();
	bool Start();
	void Update();
private:
	std::vector<prefab::CDirectionLight*> lights;
	std::vector<CVector3> poss;
};