#include "stdafx.h"
#include "Title.h"
#include "Fade.h"

Title::~Title()
{
}

bool Title::Start()
{
	fade = FindGO<Fade>("fade");
	fade->StartFadeIn();

	prefab::CSpriteRender* sp = NewGO<prefab::CSpriteRender>(0);
	sp->Init(L"sprite/cell/cell_start.dds", 250.0f, 80.529f);
	sp->SetPosition({ -490,-305,0 });
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
	switch (choice)
	{
	case start:
		break;
	case difficulty:
		break;
	case config:
		break;
	case end:
		break;
	}
}

void Title::cho_start()
{
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
