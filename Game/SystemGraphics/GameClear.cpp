#include "stdafx.h"
#include "GameClear.h"

#include "Fade.h"
#include "tkEngine/light/tkDirectionLight.h"

GameClear::~GameClear()
{
	DeleteGO(sky);
	for (auto s : lights)
	{
		DeleteGO(s);
	}
	for (auto s : runpixs)
	{
		DeleteGO(s);
	}
	for (auto s : sp_result)
	{
		DeleteGO(s);
	}
	for (auto s : sp_time)
	{
		DeleteGO(s);
	}
	for (auto s : sp_PC)
	{
		DeleteGO(s);
	}
	for (auto s : sp_score)
	{
		DeleteGO(s);
	}
}

bool GameClear::Start()
{
	fade = FindGO<Fade>("fade");
	fade->StartFadeIn();
	MainCamera().SetUpdateProjMatrixFunc(CCamera::EnUpdateProjMatrixFunc::enUpdateProjMatrixFunc_Ortho);
	MainCamera().SetPosition({ 0,0,-50 });
	MainCamera().SetTarget({ 0,0,0 });
	MainCamera().Update();

	

	CQuaternion rot;
	rot.SetRotationDeg(CVector3::AxisY, 180);
	sky = NewGO < prefab::CSkinModelRender>(0);
	sky->Init(L"modelData/map/sky_night.cmo");
	sky->SetScale({ 2.0f,2.0f,2.0f });
	sky->SetPosition({ 0,0,10 });
	//sky->SetRotation(rot);
	//sha_sky.Load("shader/model.fx", "PSsky", CShader::EnType::PS);
	//sky->FindMaterial([&](CModelEffect* mt)
	//{
	//	mt->SetRender3DModelPSShader(sha_sky);
	//});

	anim.Load(L"modelData/pixie/pixie_walk.tka");
	anim.SetLoopFlag(true);
	
	rot.SetRotationDeg(CVector3::AxisY, 90);

	prefab::CSkinModelRender* sr = NewGO < prefab::CSkinModelRender>(0);
	sr->Init(L"modelData/pixie/pixie.cmo", &anim, 1);
	sr->SetScale({ 0.7f,0.7f,0.7f });
	sr->SetPosition({ -600,250,0 });
	sr->SetRotation(rot);
	sha_sky.Load("shader/model.fx", "PSgcp", CShader::EnType::PS);
	sky->FindMaterial([&](CModelEffect* mt)
	{
		mt->SetRender3DModelPSShader(sha_sky);
	});
	runpixs.push_back(sr);

	sr = NewGO < prefab::CSkinModelRender>(0);
	sr->Init(L"modelData/pixie/pixie.cmo", &anim, 1);
	sr->SetScale({ 0.7f,0.7f,0.7f });
	sr->SetPosition({ -600,100,0 });
	sr->SetRotation(rot);
	runpixs.push_back(sr);

	sr = NewGO < prefab::CSkinModelRender>(0);
	sr->Init(L"modelData/pixie/pixie.cmo", &anim, 1);
	sr->SetScale({ 0.7f,0.7f,0.7f });
	sr->SetPosition({ -600,-50,0 });
	sr->SetRotation(rot);
	runpixs.push_back(sr);

	sr = NewGO < prefab::CSkinModelRender>(0);
	sr->Init(L"modelData/pixie/pixie.cmo", &anim, 1);
	sr->SetScale({ 0.7f,0.7f,0.7f });
	sr->SetPosition({ -600,-200,0 });
	sr->SetRotation(rot);
	runpixs.push_back(sr);


	prefab::CSpriteRender* sp = NewGO<prefab::CSpriteRender>(0);
	sp->Init(L"sprite/char/gc_r.dds", 50, 70, true);
	
	prefab::CDirectionLight* light = NewGO < prefab::CDirectionLight>(0);
	light->SetDirection({ 0,0,1 });
	light->SetColor({ 60,60,60,1.0f });
	lights.push_back(light);
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
