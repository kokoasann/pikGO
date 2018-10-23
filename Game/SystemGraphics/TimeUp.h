#pragma once

class Fade;
class opChara;
class TimeUp :public IGameObject
{
public:
	~TimeUp();
	bool Start();
	void Update();
	void SetcamPos(CVector3 v);
	void SetcamTar(CVector3 v);

	void st_st1();
	void st_eye();
	void st_fa();
	void st_cho();
	void st_waitfade();
private:
	enum State
	{
		st1,
		eye,
		fa,
		cho,
		waitfade
	};
	State state = st1;
	int cut = 0;
	bool first = true;
	float time = 0;

	std::vector<prefab::CDirectionLight*> lights;
	prefab::CSkinModelRender* sky;
	std::vector<opChara*> pixs;
	CAnimationClip anic[1];
	prefab::CSkinModelRender* damy;

	prefab::CSpriteRender* ret;
	prefab::CSpriteRender* tit;
	prefab::CSpriteRender* sel;
	int choi = 0;

	CVector3 camTar = CVector3::Zero;
	CVector3 camPos = CVector3::Zero;

	bool isMove = true;
	Fade* fade;
};