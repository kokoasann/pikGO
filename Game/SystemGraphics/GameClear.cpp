#include "stdafx.h"
#include "GameClear.h"

#include "Fade.h"

GameClear::~GameClear()
{
}

bool GameClear::Start()
{
	fade = FindGO<Fade>("fade");
	fade->StartFadeIn();
	MainCamera().SetUpdateProjMatrixFunc(CCamera::EnUpdateProjMatrixFunc::enUpdateProjMatrixFunc_Ortho);
	MainCamera().SetPosition({ 0,0,-100 });
	MainCamera().SetTarget({ 0,0,0 });
	MainCamera().Update();
	return true;
}

void GameClear::init(int pic, float time, float limit)
{
	this->pixieCount = pic;
	this->time = time;
	this->limit = limit;
	
}

void GameClear::Update()
{
}

void GameClear::PostRender(CRenderContext& rc)
{
	font.Begin(rc);
	font.End(rc);
}
