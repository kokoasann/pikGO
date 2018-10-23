#include "stdafx.h"
#include "Title.h"
#include "Fade.h"

#include "Game.h"

#include "opChara.h"
#include "tkEngine/light/tkDirectionLight.h"

Title::~Title()
{
	for (auto s : cells)
	{
		DeleteGO(s);
	}
	DeleteGO(title);
	DeleteGO(ground);
	DeleteGO(light);
}

bool Title::Start()
{
	MainCamera().SetPosition({ 0,50,0 });
	MainCamera().SetTarget({ 0,1,0.1f });
	MainCamera().SetUpdateProjMatrixFunc(CCamera::EnUpdateProjMatrixFunc::enUpdateProjMatrixFunc_Perspective);
	MainCamera().Update();
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

	title = NewGO<prefab::CSpriteRender>(0);
	title->Init(L"sprite/title.dds", 1028*0.7f, 542*0.7f);
	title->SetPosition({ -220,150,0 });

	ground = NewGO<prefab::CSkinModelRender>(0);
	ground->Init(L"modelData/op/Ground.cmo");

	light = NewGO<prefab::CDirectionLight>(0);
	light->SetDirection({ 0,-1,0 });
	light->SetColor({ 300,300,300,1 });
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

void Title::pic_spw()
{
}
