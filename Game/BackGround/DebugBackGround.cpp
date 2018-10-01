#include "stdafx.h"
#include "DebugBackGround.h"

#include "Player.h"
#include "Pixie/Pixie.h"
#include "BackGround/BackGround.h"

#include "Game.h"

bool DebugBG::Start()
{
	float BASE = 1.0f / 3.0f;
	Game* game = FindGO<Game>("game");
	tx = game->T*3;
	yy = game->Y*3;
	BG = FindGO<BackGround>("BG");
	map = BG->map;

	player = FindGO<Player>("player");
	QueryGOs<Pixie>("pixie", [&](Pixie* pi)->bool
	{
		Marker pic;
		pic.x = round(pi->Getpos().z / 1000.0f / BASE);
		pic.y = round(pi->Getpos().x / 1000.0f / BASE);
		pic.old = map[pic.y][pic.x];
		PI.push_back(pic);
		return true;
	});
	return true;
}

void DebugBG::Update()
{
	float BASE = 1.0f / 3.0f;
	map[PL.y][PL.x] = PL.old;
	PL.x = round(player->Getpos().z / 1000.0f / BASE);
	PL.y = round(player->Getpos().x / 1000.0f / BASE);
	PL.old = map[PL.y][PL.x];
	
	int i = 0;
	QueryGOs<Pixie>("pixie", [&](Pixie* pi)->bool
	{
		map[PI[i].y][PI[i].x] = PI[i].old;
		PI[i].x = round(pi->Getpos().z / 1000.0f / BASE);
		PI[i].y = round(pi->Getpos().x / 1000.0f / BASE);
		PI[i].old = map[PI[i].y][PI[i].x];
		
		i++;
		return true;
	});

	map[PL.y][PL.x] = 8;
	for (auto pi : PI)
	{
		map[pi.y][pi.x] = 9;
	}
}

void DebugBG::PostRender(CRenderContext & rc)
{
	font.Begin(rc);
	float px = -300;
	float py = -300;
	for (int x = 0; x < tx; x++)
	{
		for (int y = 0; y < yy; y++)
		{
			wchar_t n[256];
			int num = map[x][y];
			swprintf_s(n, L"%01d", num);
			font.Draw(n, { px - y * 10,py + x * 10 }, CVector4::White, 0, 0.35f);
		}
	}
	font.End(rc);
}
