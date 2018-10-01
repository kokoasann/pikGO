#pragma once

class Player;
class Pixie;
class BackGround;
struct Marker
{
	int x;
	int y;
	int old;
};
class DebugBG :public IGameObject
{
public:
	bool Start();
	void Update();
	void PostRender(CRenderContext &rc);
	CFont font;

	const float BASE = 1.0f / 3.0f;
	
	int tx;
	int yy;
	int** map;
	
	Marker PL;
	std::vector<Marker> PI;

	Player* player;
	Pixie* p;
	BackGround* BG;
};