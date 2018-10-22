#include "stdafx.h"
#include "GameClear.h"
#include "opChara.h"

#include "SaveLoad/SaveLoad.h"
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
	if (firstfade)
	{
		fade = FindGO<Fade>("fade");
		fade->StartFadeIn();
		sky = NewGO<prefab::CSkinModelRender>(0);
		sky->Init(L"modelData/map/sky_night.cmo");
		sky->SetScale({ 2.0f,2.0f,2.0f });
		sky->SetPosition({ 0,300,50 });
		//sky->SetRotation(rot);
		/*sha_sky.Load("shader/model.fx", "PSsky", CShader::EnType::PS);
		sky->FindMaterial([&](CModelEffect* mt)
		{
			mt->SetRender3DModelPSShader(sha_sky);
		});*/
		firstfade = false;
	}
	if (fade->IsFade())
		return false;


	fade->SetFadeSpeed(20);
	MainCamera().SetUpdateProjMatrixFunc(CCamera::EnUpdateProjMatrixFunc::enUpdateProjMatrixFunc_Ortho);
	MainCamera().SetPosition({ 0,0,-50 });
	MainCamera().SetTarget({ 0,0,0 });
	MainCamera().Update();

	

	CQuaternion rot;
	

	anim.Load(L"modelData/pixie/pixie_walk.tka");
	anim.SetLoopFlag(true);
	
	rot.SetRotationDeg(CVector3::AxisY, 90);

	CVector3 move = { 3,0,0 };

	prefab::CSkinModelRender* sr = NewGO < prefab::CSkinModelRender>(0);

	sr->Init(L"modelData/pixie/pixie.cmo", &anim, 1);
	sr->SetScale({ 0.7f,0.7f,0.7f });
	//sr->SetPosition({ -600,250,0 });
	opChara* oc = NewGO<opChara>(0);
	oc->init(sr, { -610,250,0 });
	sha_sky.Load("shader/model.fx", "PSgcp", CShader::EnType::PS);
	sr->FindMaterial([&](CModelEffect* mt)
	{
		mt->SetRender3DModelPSShader(sha_sky);
	});
	//oc->SetRot(rot);
	oc->chenGo();
	oc->SetMove(move);
	runpixs.push_back(oc);

	sr = NewGO < prefab::CSkinModelRender>(0);
	sr->Init(L"modelData/pixie/pixie.cmo", &anim, 1);
	sr->SetScale({ 0.7f,0.7f,0.7f });
	oc = NewGO<opChara>(0);
	oc->init(sr, { -1120,100,0 });
	//oc->SetRot(rot);
	oc->chenGo();
	oc->SetMove(move);
	runpixs.push_back(oc);

	sr = NewGO < prefab::CSkinModelRender>(0);
	sr->Init(L"modelData/pixie/pixie.cmo", &anim, 1);
	sr->SetScale({ 0.7f,0.7f,0.7f });
	oc = NewGO<opChara>(0);
	oc->init(sr, { -1120,-50,0 });
	//oc->SetRot(rot);
	oc->chenGo();
	oc->SetMove(move);
	runpixs.push_back(oc);

	sr = NewGO < prefab::CSkinModelRender>(0);
	sr->Init(L"modelData/pixie/pixie.cmo", &anim, 1);
	sr->SetScale({ 0.7f,0.7f,0.7f });
	oc = NewGO<opChara>(0);
	oc->init(sr, { -1120,-200,0 });
	//oc->SetRot(rot);
	oc->chenGo();
	oc->SetMove(move);
	runpixs.push_back(oc);


	prefab::CSpriteRender* sp = NewGO<prefab::CSpriteRender>(0);
	rot.SetRotationDeg(CVector3::AxisY, 90);
	//result sprite
	{
		sp->Init(L"sprite/char/gc_r.dds", 50, 70, true);
		sp->SetPosition({ -125,280,20 });
		sp->SetRotation(rot);
		sp_result.push_back(sp);

		sp = NewGO<prefab::CSpriteRender>(0);
		sp->Init(L"sprite/char/gc_e.dds", 50, 70, true);
		sp->SetPosition({ -75,280,20 });
		sp->SetRotation(rot);
		sp_result.push_back(sp);

		sp = NewGO<prefab::CSpriteRender>(0);
		sp->Init(L"sprite/char/gc_s.dds", 50, 70, true);
		sp->SetPosition({ -25,280,20 });
		sp->SetRotation(rot);
		sp_result.push_back(sp);

		sp = NewGO<prefab::CSpriteRender>(0);
		sp->Init(L"sprite/char/gc_u.dds", 50, 70, true);
		sp->SetPosition({ 25,280,20 });
		sp->SetRotation(rot);
		sp_result.push_back(sp);

		sp = NewGO<prefab::CSpriteRender>(0);
		sp->Init(L"sprite/char/gc_l.dds", 50, 70, true);
		sp->SetPosition({ 75,280,20 });
		sp->SetRotation(rot);
		sp_result.push_back(sp);

		sp = NewGO<prefab::CSpriteRender>(0);
		sp->Init(L"sprite/char/gc_t.dds", 50, 70, true);
		sp->SetPosition({ 125,280,20 });
		sp->SetRotation(rot);
		sp_result.push_back(sp);
	}
	
	//time sprite
	{
		sp = NewGO<prefab::CSpriteRender>(0);
		sp->Init(L"sprite/char/gc_t.dds", 50, 70, true);
		sp->SetPosition({ -500,130,20 });
		sp->SetRotation(rot);
		sp_time.push_back(sp);

		sp = NewGO<prefab::CSpriteRender>(0);
		sp->Init(L"sprite/char/gc_i.dds", 50, 70, true);
		sp->SetPosition({ -450,130,20 });
		sp->SetRotation(rot);
		sp_time.push_back(sp);

		sp = NewGO<prefab::CSpriteRender>(0);
		sp->Init(L"sprite/char/gc_m.dds", 50, 70, true);
		sp->SetPosition({ -400,130,20 });
		sp->SetRotation(rot);
		sp_time.push_back(sp);

		sp = NewGO<prefab::CSpriteRender>(0);
		sp->Init(L"sprite/char/gc_e.dds", 50, 70, true);
		sp->SetPosition({ -350,130,20 });
		sp->SetRotation(rot);
		sp_time.push_back(sp);
	}

	//pixies sprite
	{
		sp = NewGO<prefab::CSpriteRender>(0);
		sp->Init(L"sprite/char/gc_p.dds", 50, 70, true);
		sp->SetPosition({ -600,-20,20 });
		sp->SetRotation(rot);
		sp_PC.push_back(sp);

		sp = NewGO<prefab::CSpriteRender>(0);
		sp->Init(L"sprite/char/gc_i.dds", 50, 70, true);
		sp->SetPosition({ -550,-20,20 });
		sp->SetRotation(rot);
		sp_PC.push_back(sp);

		sp = NewGO<prefab::CSpriteRender>(0);
		sp->Init(L"sprite/char/gc_x.dds", 50, 70, true);
		sp->SetPosition({ -500,-20,20 });
		sp->SetRotation(rot);
		sp_PC.push_back(sp);

		sp = NewGO<prefab::CSpriteRender>(0);
		sp->Init(L"sprite/char/gc_i.dds", 50, 70, true);
		sp->SetPosition({ -450,-20,20 });
		sp->SetRotation(rot);
		sp_PC.push_back(sp);

		sp = NewGO<prefab::CSpriteRender>(0);
		sp->Init(L"sprite/char/gc_e.dds", 50, 70, true);
		sp->SetPosition({ -400,-20,20 });
		sp->SetRotation(rot);
		sp_PC.push_back(sp);

		sp = NewGO<prefab::CSpriteRender>(0);
		sp->Init(L"sprite/char/gc_s.dds", 50, 70, true);
		sp->SetPosition({ -350,-20,20 });
		sp->SetRotation(rot);
		sp_PC.push_back(sp);
	}

	//score sprite
	{
		sp = NewGO<prefab::CSpriteRender>(0);
		sp->Init(L"sprite/char/gc_s.dds", 50, 70, true);
		sp->SetPosition({ -550,-170,20 });
		sp->SetRotation(rot);
		sp_score.push_back(sp);

		sp = NewGO<prefab::CSpriteRender>(0);
		sp->Init(L"sprite/char/gc_c.dds", 50, 70, true);
		sp->SetPosition({ -500,-170,20 });
		sp->SetRotation(rot);
		sp_score.push_back(sp);

		sp = NewGO<prefab::CSpriteRender>(0);
		sp->Init(L"sprite/char/gc_o.dds", 50, 70, true);
		sp->SetPosition({ -450,-170,20 });
		sp->SetRotation(rot);
		sp_score.push_back(sp);

		sp = NewGO<prefab::CSpriteRender>(0);
		sp->Init(L"sprite/char/gc_r_l.dds", 50, 70, true);
		sp->SetPosition({ -400,-170,20 });
		sp->SetRotation(rot);
		sp_score.push_back(sp);

		sp = NewGO<prefab::CSpriteRender>(0);
		sp->Init(L"sprite/char/gc_e.dds", 50, 70, true);
		sp->SetPosition({ -350,-170,20 });
		sp->SetRotation(rot);
		sp_score.push_back(sp);
	}

	prefab::CDirectionLight* light = NewGO < prefab::CDirectionLight>(0);
	light->SetDirection({ 0,0,1 });
	light->SetColor({ 10,10,10,1.0f });
	lights.push_back(light);
	return true;
}

void GameClear::init(int pic, float time, float limit)
{
	this->pixieCount = pic;
	this->time = time;
	this->limit = limit;
	
	this->score = (int)((limit - time) / limit * pic * 100.0f);
}

void GameClear::Update()
{
	CVector3 v;
	for (auto s : sp_result)
	{
		v = s->GetPosition();
		v.z = 0;
		v -= runpixs[0]->GetPos();
		if (v.Length() <= 32)
		{
			CQuaternion rot = CQuaternion::Identity;
			s->SetRotation(rot);
		}
	}

	for (auto s : sp_time)
	{
		v = s->GetPosition();
		v.z = 0;
		v -= runpixs[1]->GetPos();
		if (v.Length() <= 32)
		{
			CQuaternion rot = CQuaternion::Identity;
			s->SetRotation(rot);
		}
	}

	for (auto s : sp_PC)
	{
		v = s->GetPosition();
		v.z = 0;
		v -= runpixs[2]->GetPos();
		if (v.Length() <= 32)
		{
			CQuaternion rot = CQuaternion::Identity;
			s->SetRotation(rot);
		}
	}

	for (auto s : sp_score)
	{
		v = s->GetPosition();
		v.z = 0;
		v -= runpixs[3]->GetPos();
		if (v.Length() <= 32)
		{
			CQuaternion rot = CQuaternion::Identity;
			s->SetRotation(rot);
		}
	}

	if (runpixs[0]->GetPos().x > -150 && runpixs[0]->GetPos().x < 150)
	{
		prefab::CEffect* effe = NewGO<prefab::CEffect>(0);
		effe->Play(L"effect/krkr.efk");
		effe->SetScale({ 20,20,20 });
		effe->SetPosition(runpixs[0]->GetPos());
	}

	if (runpixs[1]->GetPos().x > -525 && runpixs[1]->GetPos().x < -375)
	{
		prefab::CEffect* effe = NewGO<prefab::CEffect>(0);
		effe->Play(L"effect/krkr.efk");
		effe->SetScale({ 20,20,20 });
		effe->SetPosition(runpixs[1]->GetPos());
	}

	if (runpixs[2]->GetPos().x > -625 && runpixs[2]->GetPos().x < -375)
	{
		prefab::CEffect* effe = NewGO<prefab::CEffect>(0);
		effe->Play(L"effect/krkr.efk");
		effe->SetScale({ 20,20,20 });
		effe->SetPosition(runpixs[2]->GetPos());
	}

	if (runpixs[3]->GetPos().x > -575 && runpixs[3]->GetPos().x < -375)
	{
		prefab::CEffect* effe = NewGO<prefab::CEffect>(0);
		effe->Play(L"effect/krkr.efk");
		effe->SetScale({ 20,20,20 });
		effe->SetPosition(runpixs[3]->GetPos());
	}

	if (fabsf(runpixs[1]->GetPos().x) < 10.0f)
	{
		fontdisp = true;
	}
}

void GameClear::PostRender(CRenderContext& rc)
{
	if (!fontdisp)
		return;
	font.Begin(rc);
	wchar_t text[256];
	swprintf_s(text, L"%02f", time);
	font.Draw(text, { 0,130 }, {1,1,1,fontalph}, 0, 1);

	swprintf_s(text, L"%d", pixieCount);
	font.Draw(text, { 0,-20 }, { 1,1,1,fontalph }, 0, 1);

	swprintf_s(text, L"%d", score);
	font.Draw(text, { 0,-170 }, { 1,1,1,fontalph }, 0, 1);
	font.End(rc);
	fontalph += 0.04f*GameTime().GetFrameDeltaTime();
}
