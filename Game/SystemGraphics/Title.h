#pragma once

class Fade;
class opChara;
class Title :public IGameObject
{
public:
	~Title();
	bool Start();
	void Update();
	
	void cho_start();
	void cho_difficulty();
	void cho_config();
	void cho_end();

	void pic_spw();
private:
	enum Choice
	{
		start,
		difficulty,
		
		config,
		end,
	};
	Choice choice = start;
	bool isMove = true;

	prefab::CDirectionLight* light;
	prefab::CSkinModelRender* ground;
	prefab::CSpriteRender* title;
	std::vector<prefab::CSpriteRender*> cells;

	Fade* fade;

	CVector4 mulcolor = { 25.0f,25.0f,25.0f,1 };

	bool isStart = false;

	enum pixs
	{
		one,
		formation,
		bigwave,
	};
	pixs p = one;
	std::vector<opChara*> ps;
};