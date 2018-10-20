#include "stdafx.h"
#include "Title.h"
#include "Fade.h"

#include "Game.h"

Title::~Title()
{
	for (auto s : cells)
	{
		DeleteGO(s);
	}
}

bool Title::Start()
{
	fade = FindGO<Fade>("fade");
	fade->StartFadeIn();

	prefab::CSpriteRender* sp = NewGO<prefab::CSpriteRender>(0);
	sp->Init(L"sprite/cell/cell_start.dds", 250.0f, 80.529f);
	sp->SetPosition({ -490,-305,0 });
	sp->SetMulColor(mulcolor);
	cells.push_back(sp);

	sp = NewGO<prefab::CSpriteRender>(0);
	sp->Init(L"sprite/cell/cell_diff.dds", 250.0f, 80.529f);
	sp->SetPosition({ -230,-305,0 });
	cells.push_back(sp);

	sp = NewGO<prefab::CSpriteRender>(0);
	sp->Init(L"sprite/cell/cell_config.dds", 250.0f, 80.529f);
	sp->SetPosition({ 30,-305,0 });
	cells.push_back(sp);

	sp = NewGO<prefab::CSpriteRender>(0);
	sp->Init(L"sprite/cell/cell_end.dds", 250.0f, 80.529f);
	sp->SetPosition({ 290,-305,0 });
	cells.push_back(sp);
	return true;
}

void Title::Update()
{
	if (!isStart)
	{
		if (Pad(0).GetLStickXF() >= 0.5f && isMove)
		{
			if (choice != end)
			{
				cells[choice]->SetMulColor({ 1,1,1,1 });
				choice = (Choice)((int)choice + 1);
				cells[choice]->SetMulColor(mulcolor);
				isMove = false;
			}
		}
		if (Pad(0).GetLStickXF() <= -0.5f && isMove)
		{
			if (choice != start)
			{
				cells[choice]->SetMulColor({ 1,1,1,1 });
				choice = (Choice)((int)choice - 1);
				cells[choice]->SetMulColor(mulcolor);
				isMove = false;
			}
		}
		if (fabsf(Pad(0).GetLStickXF()) < 0.3f)
		{
			isMove = true;
		}

		if (Pad(0).IsTrigger(enButtonB))
		{
			fade->SetFadeSpeed(10);
			fade->StartFadeOut();
			isStart = true;

			/*switch (choice)
			{
			case start:
				cho_start();
				break;
			case difficulty:
				cho_difficulty();
				break;
			case config:
				cho_config();
				break;
			case end:
				cho_end();
				break;
			}*/
		}
	}
	else
	{
		if (fade->IsFade())
			return;
		switch (choice)
		{
		case start:
			cho_start();
			break;
		case difficulty:
			cho_difficulty();
			break;
		case config:
			cho_config();
			break;
		case end:
			cho_end();
			break;
		}
	}
}

void Title::cho_start()
{
	NewGO<Game>(0, "game");
	DeleteGO(this);
}

void Title::cho_difficulty()
{
}

void Title::cho_config()
{
}

void Title::cho_end()
{
	exit(0);
}
