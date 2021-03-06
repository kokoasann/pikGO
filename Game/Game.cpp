#include "stdafx.h"
#include "Game.h"
#include "Creature/CreatureManager.h"
#include "BackGround/BackGround.h"
#include "BackGround/Lighting.h"
#include "Q/Q.h"
#include "SystemGraphics/Loading.h"
#include "SystemGraphics/Timer.h"
#include "Player.h"
#include "Pixie/Pixie.h"
#include "Pixie/PixieSpawner.h"
#include "Enemy/EnemySpawner.h"
#include "Camera/GameCamera.h"
#include "BackGround/RootFind.h"
#include "SystemGraphics/Fade.h"
#include "SystemGraphics/GameClear.h"
#include "SystemGraphics/TimeUp.h"
#include "tkEngine/light/tkDirectionLight.h"

#include "test/test.h"
#include "BackGround/DebugBackGround.h"

Game::Game()
{
	//DeleteGO(m_skinModelRender);
}


Game::~Game()
{
	DeleteGO(player);
	DeleteGO(bg);
	DeleteGO(FindGO<GameCamera>("camera"));
	DeleteGO(RF);
	DeleteGO(lighting);
	DeleteGO(timer);
	DeleteGO(FindGO<Q>("q"));
	QueryGOs<Pixie>("pixie", [&](auto obj)->bool
	{
		DeleteGO(obj);
		return true;
	});
	DeleteGO(FindGO<CreatureManager>("CM"));
}
bool Game::Start()
{
	CQuaternion ad;
	switch (initStep) {
	case enInitStep_00:
		MainCamera().SetTarget({ 15000.1f, -10.0f, 15000.0f });
		MainCamera().SetNear(1.0f);
		MainCamera().SetFar(50000.0f);
		MainCamera().SetPosition({ 15000.0f, 9500.0f, 15000.0f });
		//MainCamera().SetViewAngle(90);
		MainCamera().Update();

		//o = NewGO<prefab::CSpriteRender>(1);
		//o->Init(L"sprite/point.dds", 50, 50);
		lod = NewGO<Loading>(1, "loading");
		fade = FindGO<Fade>("fade");

		sr = NewGO < prefab::CSkinModelRender>(0);
		sr->Init(L"modelData/map/start.cmo");
		sr->Init(L"modelData/map/end.cmo");
		sr->Init(L"modelData/map/right.cmo");
		sr->Init(L"modelData/map/leftkarb.cmo");
		sr->Init(L"modelData/map/rightkarb.cmo");
		sr->Init(L"modelData/map/tile.cmo");
		DeleteGO(sr);
		
		//カメラを設定。
		MainCamera().SetTarget({ 5000.1f, -0.0001f, 1000.0f });
		MainCamera().SetNear(1.0f);
		MainCamera().SetFar(50000.0f);
		MainCamera().SetPosition({ 5000.0f, 10500.0f, 1000.0f });
		MainCamera().SetUpdateProjMatrixFunc(CCamera::EnUpdateProjMatrixFunc::enUpdateProjMatrixFunc_Perspective);
		MainCamera().SetViewAngle(20);
		MainCamera().Update();
		//int T = 10, Y = 10;

		NewGO<CreatureManager>(0, "CM");

		NewGO<GameCamera>(0, "camera");

		player = NewGO<Player>(0, "player");

		NewGO<Q>(0, "q");

		bg = NewGO<BackGround>(0, "BG");
		bg->init(T, Y);
		//bg->TestMaping();
		initStep = enInitStep_01;
		break;
	case enInitStep_01:
		/*ad.SetRotationDeg(CVector3::AxisX, 1.0f);
		oRot.Multiply(oRot, ad);
		o->SetRotation(oRot);*/
		if (bg->GetInitEnd() == true) {
			//BGの構築終わり。
			DeleteGO(lod);
			bg->SetUP();
			fade->StartFadeIn();
			initStep = enInitStep_02;
		}
		break;
	case enInitStep_02:
		
		
		
		if (fade->IsFade())
			return false;
		fade->SetFadeSpeed(20);
		timer = NewGO<Timer>(0, "timer");

		RF = NewGO<RootFind>(0, "RF");
		RF->CreateNodeMap(T,Y,bg->GetMap());
		RF->BuildNode();

		ps = NewGO<PixieSpawner>(0, "PS");
		//es = NewGO<EnemySpawner>(0, "ES");
		ps->init(T, Y,10, 5);
		//ps->TestSpawn();
		//es->init(T, Y, 1, 0);

		//NewGO<Pixie>(0, "pixie");

		lighting = NewGO<Lighting>(0, "light");

		point = NewGO < prefab::CSpriteRender>(0);
		point->Init(L"sprite/point.dds", 24, 24);

		//NewGO<DebugBG>(0, "DBG");

		//NewGO<test>(0,"test");
		return true;
	}
	return false;
}

void Game::Update()
{
	if (Clear && !(fade->IsFade()))
	{
		GameClear* GC = NewGO<GameClear>(0, "GC");
		GC->init(pixieoCount, timer->getTime(), timer->getLimit());

		DeleteGO(this);
	}
	if (player->GetIsClear() && !(fade->IsFade()) && !Clear)
	{
		fade->changeWhite();
		fade->SetFadeSpeed(0.5f);
		fade->StartFadeOut();
		DeleteGO(point);
		timer->DelRen();
		Clear = true;
	}

	if (TimeOver && !fade->IsFade())
	{
		NewGO<TimeUp>(0, "timeup");
		DeleteGO(point);
		DeleteGO(this);
	}
}

void Game::PostRender(CRenderContext & rc)
{
	pixieoCount = 0;
	QueryGOs<Pixie>("pixie", [&](Pixie* p)->bool
	{
		if (p->GetMode() == Pixie::Mode::chase)
		{
			pixieoCount += 1;
		}
		return true;
	});
	font.Begin(rc);
	wchar_t tex[256];
	swprintf_s(tex, L"pixies:%d", pixieoCount);
	font.Draw(tex, { -340,-230 });
	font.End(rc);
}
