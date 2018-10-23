#include "stdafx.h"
#include "TimeUp.h"
#include "Game.h"
#include "Title.h"

#include "opChara.h"
#include "Fade.h"
#include "tkEngine/light/tkDirectionLight.h"

TimeUp::~TimeUp()
{
	for (auto s : pixs)
	{
		DeleteGO(s);
	}
	for (auto s : lights)
	{
		DeleteGO(s);
	}
	DeleteGO(sky);
	DeleteGO(damy);
	DeleteGO(sel);
	DeleteGO(ret);
	DeleteGO(tit);
}

bool TimeUp::Start()
{
	if (first)
	{
		fade = FindGO<Fade>("fade");
		fade->StartFadeIn();

		SetcamPos({ 0,50,-50 });
		SetcamTar({ 0,130,50 });
		CVector3 cmp = { 0,0,-50 };

		prefab::CDirectionLight* li = NewGO<prefab::CDirectionLight>(0);
		li->SetDirection({ 0,-0.707f,-0.707f });
		li->SetColor({ 30,30,30,1 });
		lights.push_back(li);
		
		anic[0].Load(L"modelData/pixie/pixie_idle.tka");
		anic[0].SetLoopFlag(true);

		prefab::CSkinModelRender* sr = NewGO<prefab::CSkinModelRender>(0);
		sr->Init(L"modelData/pixie/pixie.cmo", anic, 1);
		opChara* oc = NewGO<opChara>(0);
		CVector3 v = { 50,0,30 };
		oc->init(sr, v);
		v = cmp - v;
		v.Normalize();
		v *= 3;
		oc->SetMove(v);
		oc->chenGo();
		oc->chenRota();
		oc->playAnim(0);
		pixs.push_back(oc);

		sr = NewGO<prefab::CSkinModelRender>(0);
		sr->Init(L"modelData/pixie/pixie.cmo", anic, 1);
		sr->SetShadowCasterFlag(true);
		sr->SetShadowReceiverFlag(true);
		oc = NewGO<opChara>(0);
		v = { 0.1f,0,30 };
		oc->init(sr, v);
		v = cmp - v;
		v.Normalize();
		v *= 3;
		oc->SetMove(v);
		oc->chenGo();
		oc->chenRota();
		oc->playAnim(0);
		pixs.push_back(oc);

		sr = NewGO<prefab::CSkinModelRender>(0);
		sr->Init(L"modelData/pixie/pixie.cmo", anic, 1);
		sr->SetShadowCasterFlag(true);
		sr->SetShadowReceiverFlag(true);
		oc = NewGO<opChara>(0);
		v = { -50,0,30 };
		oc->init(sr, v);
		v = cmp - v;
		v.Normalize();
		v *= 3;
		oc->SetMove(v);
		oc->chenGo();
		oc->chenRota();
		oc->playAnim(0);
		pixs.push_back(oc);

		sr = NewGO<prefab::CSkinModelRender>(0);
		sr->Init(L"modelData/pixie/pixie.cmo", anic, 1);
		sr->SetShadowCasterFlag(true);
		sr->SetShadowReceiverFlag(true);
		oc = NewGO<opChara>(0);
		v = { 25,0,45 };
		oc->init(sr, v);
		v = cmp - v;
		v.Normalize();
		v *= 3;
		oc->SetMove(v);
		oc->chenGo();
		oc->chenRota();
		oc->playAnim(0);
		pixs.push_back(oc);

		sr = NewGO<prefab::CSkinModelRender>(0);
		sr->Init(L"modelData/pixie/pixie.cmo", anic, 1);
		sr->SetShadowCasterFlag(true);
		sr->SetShadowReceiverFlag(true);
		oc = NewGO<opChara>(0);
		v = { -25,0,30 };
		oc->init(sr, v);
		v = cmp - v;
		v.Normalize();
		v *= 3;
		oc->SetMove(v);
		oc->chenGo();
		oc->chenRota();
		oc->playAnim(0);
		pixs.push_back(oc);

		sr = NewGO<prefab::CSkinModelRender>(0);
		sr->Init(L"modelData/pixie/pixie.cmo", anic, 1);
		sr->SetShadowCasterFlag(true);
		sr->SetShadowReceiverFlag(true);
		oc = NewGO<opChara>(0);
		v = { 80,0,20 };
		oc->init(sr, v);
		v = cmp - v;
		v.Normalize();
		v *= 3;
		oc->SetMove(v);
		oc->chenGo();
		oc->chenRota();
		oc->playAnim(0);
		pixs.push_back(oc);

		sr = NewGO<prefab::CSkinModelRender>(0);
		sr->Init(L"modelData/pixie/pixie.cmo", anic, 1);
		sr->SetShadowCasterFlag(true);
		sr->SetShadowReceiverFlag(true);
		oc = NewGO<opChara>(0);
		v = { -60,0,10 };
		oc->init(sr, v);
		v = cmp - v;
		v.Normalize();
		v *= 3;
		oc->SetMove(v);
		oc->chenRota();
		oc->playAnim(0);
		pixs.push_back(oc);

		sky = NewGO<prefab::CSkinModelRender>(0);
		sky->Init(L"modelData/map/sky.cmo");
		sky->SetScale({ 10,10,10 });

		damy = NewGO < prefab::CSkinModelRender>(0);
		damy->Init(L"modelData/pixie/pixie.cmo");
		damy->SetPosition({ 0,0,-100 });

		first = false;
	}
	if (fade->IsFade())
		return false;

	return true;
}

void TimeUp::Update()
{
	switch (state)
	{
	case st1:
		st_st1();
		break;
	case eye:
		st_eye();
		break;
	case fa:
		st_fa();
		break;
	case cho:
		st_cho();
		break;
	case waitfade:
		st_waitfade();
		break;
	}
}

void TimeUp::SetcamPos(CVector3 v)
{
	camPos = v;
	MainCamera().SetPosition(v);
	MainCamera().Update();
}

void TimeUp::SetcamTar(CVector3 v)
{
	camTar = v;
	MainCamera().SetTarget(v);
	MainCamera().Update();
}

void TimeUp::st_st1()
{
	CVector3 v = CVector3::Zero;
	time += GameTime().GetFrameDeltaTime();
	if (time > 3)
	{
		time = 0;
		state = fa;
		first = true;
		fade->StartFadeOut();
	}
	/*switch (cut)
	{
	case 0:
		v = { -1,0,-1 };
		SetcamTar(camTar + v);
		if (camTar.z <= 200)
			cut++;
		break;
	case 1:
		v = { 1,0,1 };
		SetcamTar(camTar + v);
		if (camTar.z >= 500)
			cut++;
		break;
	case 2:
		v = { 1,0,-1 };
		SetcamTar(camTar + v);
		if (camTar.z <= 200)
			cut++;
		break;
	case 3:
		v = { -1,0,1 };
		SetcamTar(camTar + v);
		if (camTar.z >= 500)
			cut++;
		break;
	}*/
}

void TimeUp::st_eye()
{
	if (first)
	{
		SetcamPos({ -7,90,-70 });
		SetcamTar({ -7,95.1f,-100 });
	}
}

void TimeUp::st_fa()
{
	if (fade->IsFade())
		return;
	sel = NewGO<prefab::CSpriteRender>(0);
	sel->Init(L"sprite/go/go_marker.dds", 256, 256);
	sel->SetPosition({ -486,-200,0 });
	ret = NewGO<prefab::CSpriteRender>(0);
	ret->Init(L"sprite/go/go_retry.dds", 256, 256);
	ret->SetPosition({ -486,-200,0 });
	tit = NewGO<prefab::CSpriteRender>(0);
	tit->Init(L"sprite/go/go_title.dds", 256, 256);
	tit->SetPosition({ -220,-200,0 });
	state = cho;
}

void TimeUp::st_cho()
{
	if (Pad(0).IsTrigger(enButtonB))
	{
		//fade->StartFadeOut();
		state = waitfade;
		MainCamera().SetUpdateProjMatrixFunc(CCamera::EnUpdateProjMatrixFunc::enUpdateProjMatrixFunc_Perspective);

	}
	else if (Pad(0).GetLStickXF() >= 0.5f && isMove)
	{
		if (choi != 1)
		{
			sel->SetPosition({ -220,-200,0 });
			choi++;
			isMove = false;
		}
	}
	else if (Pad(0).GetLStickXF() <= -0.5f && isMove)
	{
		if (choi != 0)
		{
			sel->SetPosition({ -486,-200,0 });
			choi--;
			isMove = false;
		}
	}
	if (fabsf(Pad(0).GetLStickXF()) < 0.3f)
	{
		isMove = true;
	}
}

void TimeUp::st_waitfade()
{
	switch (choi)
	{
	case 0:
		NewGO<Game>(0, "game");
		break;
	case 1:
		NewGO<Title>(0, "title");
		break;
	}
	DeleteGO(this);
}
