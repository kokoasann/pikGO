#pragma once

class Fade;
class opChara;
class Opening :public IGameObject
{
public:
	~Opening();
	bool Start();
	void Update();

	void SStart();
	void SSide();
	void SUp();
	void SFront();
	void SEnd();
	enum State
	{
		start,
		side,
		up,
		front,
		end
	};
	enum pixa
	{
		pix_idle,
		pix_walk,

		pix_num
	};
private:
	State state = start;
	int cut = 0;
	bool first = true;
	opChara* player;
	opChara* pix;
	std::vector<opChara*> pixies;
	prefab::CSkinModelRender* pre;
	CAnimationClip pix_anic[pix_num];

	Fade* fade;
	float time = 0;

	CLevel level;

	prefab::CSkinModelRender* sky;
	CShader shader;

	prefab::CDirectionLight* light;
	std::vector<prefab::CDirectionLight*> lightlist;
};