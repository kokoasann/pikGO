#include "stdafx.h"
#include "Game.h"
#include "BackGround/BackGround.h"
#include "Player.h"
#include "Fairy/Fairy.h"
#include "Camera/GameCamera.h"
#include "tkEngine/light/tkDirectionLight.h"

Game::Game()
{
	//DeleteGO(m_skinModelRender);
}


Game::~Game()
{
}
bool Game::Start()
{
	//�J������ݒ�B
	/*MainCamera().SetTarget({ 0.0f, 70.0f, 0.0f });
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(1000.0f);
	MainCamera().SetPosition({ 0.0f, 70.0f, 200.0f });
	MainCamera().Update();*/
	/*m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo");*/
	NewGO<Player>(0,"player");
	NewGO <BackGround>(0, "BG");
	NewGO<GameCamera>(0, "camera");

	NewGO<Fairy>(0, "f");
	
	return true;
}

void Game::Update()
{

}