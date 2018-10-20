#pragma once

class Fade;
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

	std::vector<prefab::CSpriteRender*> cells;

	Fade* fade;

	CVector4 mulcolor = { 25.0f,25.0f,25.0f,1 };

	bool isStart = false;

	
};