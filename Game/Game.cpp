#include "stdafx.h"
#include "Game.h"
#include "Creature/CreatureManager.h"
#include "BackGround/BackGround.h"
#include "Player.h"
#include "Pixie/Pixie.h"
#include "Pixie/PixieSpawner.h"
#include "Camera/GameCamera.h"
#include "tkEngine/light/tkDirectionLight.h"

#include "test/test.h"

Game::Game()
{
	//DeleteGO(m_skinModelRender);
}


Game::~Game()
{
}
bool Game::Start()
{
	//NewGO<test>(0);
	//ÉJÉÅÉâÇê›íËÅB
	/*MainCamera().SetTarget({ 0.0f, 70.0f, 0.0f });
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(1000.0f);
	MainCamera().SetPosition({ 0.0f, 70.0f, 200.0f });
	MainCamera().Update();*/
	/*m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo");*/
	NewGO<CreatureManager>(0,"CM");
	NewGO<Player>(0,"player");
	NewGO <BackGround>(0, "BG");
	NewGO<GameCamera>(0, "camera");

	NewGO<PixieSpawner>(0, "PS");
	//NewGO<Pixie>(0, "pixie");
	
	point = NewGO < prefab::CSpriteRender>(0);
	point->Init(L"sprite/point.dds", 24, 24);
	return true;
}

void Game::Update()
{

}