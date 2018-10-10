#include "stdafx.h"
#include <io.h>
#include <Fcntl.h>
#include <iostream>
#include "DebugBackGround.h"

#include "Player.h"
#include "Pixie/Pixie.h"
#include "BackGround/BackGround.h"
#include "BackGround/RootFind.h"
#include "test/test.h"

#include "Game.h"

static int** map;
bool DebugBG::Start()
{
	AllocConsole();
	/*int i = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
	*stdout = *_fdopen(i, "w");
	setvbuf(stdout, NULL, _IONBF, 0);*/

	FILE* fp = NULL;
	freopen_s(&fp, "CONOUT$", "w", stdout);

	float BASE = 1.0f / 3.0f;
	Game* game = FindGO<Game>("game");
	tx = game->GetTate()*3;
	yy = game->GetYoko()*3;
	BG = FindGO<BackGround>("BG");
	RF = FindGO<RootFind>("RF");
	map = new int*[tx];
	for (int t = 0; t < tx; t++)
	{
		map[t] = new int[yy];
	}
	for (int y = 0; y < tx; y++)
	{
		for (int x = 0; x < yy; x++)
		{
			//map[y][x] = BG->map[y][x];
			map[y][x] = RF->GetNodeMap()[y][x].mapID;
		}
	}

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
	
	obj_test = FindGO<test>("test");
	//DrawMap();
	return true;
}

void DebugBG::Update()
{
	//memset(map, 0, sizeof(map));
	const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX info = { sizeof info };
	info.dwFontSize.X = 16;
	info.dwFontSize.Y = 16;
	SetCurrentConsoleFontEx(hConsole, 0, &info);

	float BASE = 1.0f / 3.0f;
	map[PL.y][PL.x] = PL.old;
	PL.x = round(player->Getpos().z / 1000.0f / BASE)+1;
	PL.y = round(player->Getpos().x / 1000.0f / BASE)+1;
	PL.old = BG->GetMap()[PL.y][PL.x];
	
	int i = 0;
	QueryGOs<Pixie>("pixie", [&](Pixie* pi)->bool
	{
		map[PI[i].y][PI[i].x] = PI[i].old;
		//PI[i].x = (pi->Getpos().z / 1000.0f / BASE)+1;
		//PI[i].y = (pi->Getpos().x / 1000.0f / BASE)+1;
		PI[i].x = pi->GetPiece().pos.x;
		PI[i].y = pi->GetPiece().pos.y;
		PI[i].old = BG->GetMap()[PI[i].y][PI[i].x];
		
		i++;
		return true;
	});

	map[PL.y][PL.x] = 8;
	for (auto pi : PI)
	{
		map[pi.y][pi.x] = 9;
	}
	QueryGOs<Pixie>("pixie", [&](Pixie* pi)->bool
	{
		for (auto r : pi->GetPiece().root)
		{
			map[(int)r.x][(int)r.y];
		}
		return true;
	});

	/*char* ch;
	for (int x = tx - 1; x >= 0; x--)
	{
		for (int y = yy - 1; y >= 0; y--)
		{
			ch = (char*)map[x][y];
			int num = map[x][y];
			std::cout << num;
		}
		std::cout << "\n";
	}*/

	CnsRender();

}

void DebugBG::Draw()
{

	for (int x = tx - 1; x >= 0; x--)
	{
		for (int y = yy - 1; y >= 0; y--)
		{
			int num = map[x][y];
			std::cout << num;
		}
		std::cout << "\n";
	}

	std::cout << "player:" << "x:" << player->Getpos().x << "y:" << player->Getpos().y << "z:" << player->Getpos().z << "\n";
	std::cout << "test:" << "x:" << obj_test->PL.x << "y:" << obj_test->PL.y << "z:" << obj_test->PL.z << "\n";
}

void DebugBG::DrawMap()
{
	for (int x = tx - 1; x >= 0; x--)
	{
		for (int y = yy - 1; y >= 0; y--)
		{
			int num = map[x][y];
			std::cout << num;
		}
		std::cout << "\n";
	}
}

void DebugBG::CnsRender()
{
	for (int x = tx-1; x >= 0; x--)
	{
		for (int y = yy-1; y >= 0; y--)
		{
			int num = map[x][y];
			std::cout << num;
		}
		std::cout << "\n";
	}

	std::cout << "player:" << "x:" << player->Getpos().x << "y:" << player->Getpos().y << "z:" << player->Getpos().z<<"\n";
	std::cout << "test:" << "x:" << obj_test->PL.x << "y:" << obj_test->PL.y << "z:" << obj_test->PL.z<<"\n";

	//CreateConsoleScreenBuffer();
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = 0;
	pos.Y = 0;
	SetConsoleCursorPosition(handle, pos);

	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(handle, &cci);
	
	cci.bVisible = FALSE;

	SetConsoleCursorInfo(handle, &cci);
}

void DebugBG::PostRender(CRenderContext & rc)
{
	/*font.Begin(rc);
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
	px = 300;
	py = -300;
	for (int x = 0; x < tx; x++)
	{
		for (int y = 0; y < yy; y++)
		{
			wchar_t n[256];
			int num = BG->map[x][y];
			swprintf_s(n, L"%01d", num);
			font.Draw(n, { px - y * 10,py + x * 10 }, CVector4::White, 0, 0.35f);
		}
	}
	font.End(rc);*/
}
