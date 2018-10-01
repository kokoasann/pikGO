#include "stdafx.h"
#include "Game.h"
#include "Creature/CreatureManager.h"
#include "BackGround/BackGround.h"
#include "SystemGraphics/Loading.h"
#include "Player.h"
#include "Pixie/Pixie.h"
#include "Pixie/PixieSpawner.h"
#include "Enemy/EnemySpawner.h"
#include "Camera/GameCamera.h"
#include "BackGround/RootFind.h"
#include "tkEngine/light/tkDirectionLight.h"

#include "test/test.h"
#include "BackGround/DebugBackGround.h"

Game::Game()
{
	//DeleteGO(m_skinModelRender);
}


Game::~Game()
{
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

		sr = NewGO < prefab::CSkinModelRender>(0);
		sr->Init(L"modelData/map/start.cmo");
		sr->Init(L"modelData/map/end.cmo");
		sr->Init(L"modelData/map/right.cmo");
		sr->Init(L"modelData/map/leftkarb.cmo");
		sr->Init(L"modelData/map/rightkarb.cmo");
		sr->Init(L"modelData/map/tile.cmo");
		DeleteGO(sr);
		//NewGO<test>(0);
		//カメラを設定。
		MainCamera().SetTarget({ 5000.1f, -0.0001f, 5000.0f });
		MainCamera().SetNear(1.0f);
		MainCamera().SetFar(50000.0f);
		MainCamera().SetPosition({ 5000.0f, 9500.0f, 5000.0f });
		MainCamera().SetViewAngle(90);
		MainCamera().Update();
		//int T = 10, Y = 10;
		NewGO<CreatureManager>(0, "CM");
		//NewGO<GameCamera>(0, "camera");
		NewGO<Player>(0, "player");
		bg = NewGO<BackGround>(0, "BG");
		bg->init(T, Y);
		initStep = enInitStep_01;
		break;
	case enInitStep_01:
		/*ad.SetRotationDeg(CVector3::AxisX, 1.0f);
		oRot.Multiply(oRot, ad);
		o->SetRotation(oRot);*/
		if (bg->iniend == true) {
			//BGの構築終わり。
			DeleteGO(lod);
			bg->SetUP();
			initStep = enInitStep_02;
		}
		break;
	case enInitStep_02:
		RF = NewGO<RootFind>(0, "RF");
		RF->CreateNodeMap(T,Y,bg->map);
		RF->BuildNode();

		ps = NewGO<PixieSpawner>(0, "PS");
		//es = NewGO<EnemySpawner>(0, "ES");
		ps->init(T, Y, 10, 0);
		//es->init(T, Y, 10, 0);
		//NewGO<Pixie>(0, "pixie");

		point = NewGO < prefab::CSpriteRender>(0);
		point->Init(L"sprite/point.dds", 24, 24);

		NewGO<DebugBG>(0, "DBG");
		return true;
	}
	return false;
}

void Game::Update()
{

}

void Game::PostRender(CRenderContext & rc)
{
}
