#pragma once

class Fade;
class opChara;
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
	int score = 0;

	prefab::CSkinModelRender* sky;
	std::list<prefab::CDirectionLight*> lights;

	CShader sha_sky;
	std::vector<opChara*> runpixs;
	CAnimationClip anim;

	std::vector<prefab::CSpriteRender*> sp_result;
	std::vector<prefab::CSpriteRender*> sp_time;
	std::vector<prefab::CSpriteRender*> sp_PC;
	std::vector<prefab::CSpriteRender*> sp_score;

	CFont font;
	bool fontdisp = false;
	float fontalph = 0.0f;

	Fade* fade;
	bool firstfade = true;
};