#pragma once

class Player;
class Pixie;
class BackGround;
class RootFind;
class test;
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
	void Draw();
	void DrawMap();
	void CnsRender();
	void PostRender(CRenderContext &rc);

private:
	CFont font;
	std::vector<char*> scr;

	const float BASE = 1.0f / 3.0f;
	
	int tx;
	int yy;
	//int** map;
	
	Marker PL;
	std::vector<Marker> PI;

	Player* player;
	Pixie* p;
	BackGround* BG;
	RootFind* RF;
	test* obj_test;
};