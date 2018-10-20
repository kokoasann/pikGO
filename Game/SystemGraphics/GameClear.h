#pragma once

class Fade;
class GameClear :public IGameObject
{
public:
	~GameClear();
	bool Start();
	void init(int pic, float time, float limit);
	void Update();
	void PostRender(CRenderContext& rc);

private:
	int pixieCount = 0;
	float time = 0.0f;
	float limit = 0.0f;
	int result = 0;
	std::vector<prefab::CSkinModelRender*> runpixs;

	std::vector<prefab::CSpriteRender*> sp_result;
	std::vector<prefab::CSpriteRender*> sp_time;
	std::vector<prefab::CSpriteRender*> sp_PC;

	CFont font;

	Fade* fade;
};