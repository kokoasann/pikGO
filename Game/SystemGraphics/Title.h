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

	std::vector<prefab::CSpriteRender*> cells;

	Fade* fade;
};