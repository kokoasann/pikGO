#include "stdafx.h"
#include "Opening.h"
#include "opChara.h"
#include "Title.h"
#include "Fade.h"
#include "tkEngine/light/tkDirectionLight.h"

Opening::~Opening()
{
	DeleteGO(player);
	//DeleteGO(pre);
	DeleteGO(sky);
	for (auto p : pixies)
	{
		if(p != nullptr)
			DeleteGO(p);
	}
	for (prefab::CDirectionLight* l : lightlist)
	{
		DeleteGO(l);
	}
	
}

bool Opening::Start()
{
	MainCamera().SetPosition({ -250.0f,450.0f,130.0f });
	MainCamera().SetTarget({ 100.0f,0.0f,0.0f });
	MainCamera().SetFar(99999.9f);
	MainCamera().SetNear(1.0f);
	MainCamera().SetViewAngle(20.0f);
	MainCamera().Update();

	CVector3 ppo = { -300.0f,0.0f,500.0f };
	pre = NewGO<prefab::CSkinModelRender>(0);
	pre->Init(L"modelData/unityChan.cmo");
	pre->SetShadowCasterFlag(true);
	pre->SetShadowReceiverFlag(true);
	player = NewGO<opChara>(0, "pla");
	player->init(pre,ppo);
	player->chenGo();
	CVector3 v = ppo * -1;
	v.Normalize();
	v *= 3;
	player->SetMove(v);

	pix_anic[pix_idle].Load(L"modelData/pixie/pixie_idle.tka");
	pix_anic[pix_idle].SetLoopFlag(true);
	pix_anic[pix_walk].Load(L"modelData/pixie/pixie_walk.tka");
	pix_anic[pix_walk].SetLoopFlag(true);

	pre = NewGO < prefab::CSkinModelRender>(0);
	pre->Init(L"modelData/pixie/pixie.cmo",pix_anic,pix_num);
	pre->SetShadowCasterFlag(true);
	pre->SetShadowReceiverFlag(true);
	pix = NewGO<opChara>(0, "pix");
	pix->init(pre, CVector3::Zero);
	pix->playAnim(pix_idle);
	pixies.push_back(pix);

	fade = FindGO<Fade>("fade");
	fade->StartFadeIn();

	level.Init(L"level/LopStart.tkl", [&](auto &obj)->bool
	{
		obj.position *= 3;
		obj.position.z += 250;
		obj.scale *= 3;
		return false;
	});

	sky = NewGO<prefab::CSkinModelRender>(0, "sky");
	sky->Init(L"modelData/map/sky.cmo");
	sky->SetScale({ 100,100,100 });
	shader.Load("shader/model.fx","PSsky", CShader::EnType::PS);
	sky->FindMaterial([&](CModelEffect* mf)
	{
		mf->SetRender3DModelPSShader(shader);
	});

	light = NewGO<prefab::CDirectionLight>(0);
	light->SetColor({ 10,10,10,0.5f });
	light->SetDirection({ -0.707f,-0.3f,0 });
	lightlist.push_back(light);

	light = NewGO<prefab::CDirectionLight>(0);
	light->SetColor({ 0,1,5,0.2f });
	light->SetDirection({ 0.35f,0.707f,0.2f });
	lightlist.push_back(light);

	light = NewGO<prefab::CDirectionLight>(0);
	light->SetColor({ 2.0f,2,2.2f,0.2f });
	light->SetDirection({ 0.707f,0.707f,0 });
	lightlist.push_back(light);

	light = NewGO<prefab::CDirectionLight>(0);
	light->SetColor({ 0.1f,3,0.2f,0.2f });
	light->SetDirection({ 0,1,0 });
	lightlist.push_back(light);
	return true;
}

void Opening::Update()
{
	if (Pad(0).IsTrigger(enButtonB))
	{
		fade->StartFadeOut();
		state = end;
		cut = 1;
		first = true;
		time = 0.0f;
	}
	switch (state)
	{
	case start:
		SStart();
		break;
	case side:
		SSide();
		break;
	case up:
		SUp();
		break;
	case front:
		SFront();
		break;
	case end:
		SEnd();
		break;
	}
}

void Opening::SStart()
{
	CVector3 v;
	switch (cut)
	{
	case 0:
		v = player->GetPos();
		if (v.Length() < 80.0f)
		{
			player->chenIdle();
			pix->chenRota();
			pix->SetRotSpeed(10);
			pix->SetMove(player->GetPos() - pix->GetPos());
			cut = 1;
		}
		break;
	case 1:
		if (time > 2)
		{
			cut = 2;
			time = 0.0f;
		}
		time += GameTime().GetFrameDeltaTime();
		break;
	case 2:
		if (first)
		{
			player->chenGo();
			player->SetRotSpeed(15);
			v = MainCamera().GetPosition();
			v.y = 0;
			v -= player->GetPos();
			v.Normalize();
			v *= 3;
			player->SetMove(v);
			pix->chenGo();
			pix->SetMove(v);

			pix->playAnim(pix_walk);
			//first = false;
			cut = 3;
		}
		break;
	case 3:
		if (time > 3)
		{
			if (first)
			{
				fade->StartFadeOut();
				first = false;
			}
			else if (!fade->IsFade())
			{
				state = side;
				time = 0.0f;
				cut = 0;
				first = true;
			}
		}
		else
		{
			time += GameTime().GetFrameDeltaTime();
			
		}
		break;
	}
	
	
}

void Opening::SSide()
{
	CVector3 v;
	switch (cut)
	{
	case 0:
		level.AllClear();
		level.Init(L"level/LopSide.tkl", [&](auto &obj)->bool
		{
			obj.position *= 5;
			obj.position.x += 800;
			obj.position.z += 300;
			
			obj.scale *= 5;
			return false;
		});
		fade->StartFadeIn();
		MainCamera().SetPosition({ 800,200,-2000 });
		MainCamera().SetTarget({ 800,200,0 });
		//MainCamera().SetViewAngle(10);
		MainCamera().SetUpdateProjMatrixFunc(CCamera::enUpdateProjMatrixFunc_Ortho);
		//MainCamera().SetUpdateProjMatrixFunc(CCamera::enUpdateProjMatrixFunc_Perspective);
		MainCamera().Update();
		player->SetPos({ 0,0,0 });
		pix->SetPos({ -50,0,0 });
		player->SetMove({ 3,0,0 });
		pix->SetMove({ 3,0,0 });
		player->SetScale({ 0.7f,0.7f,0.7f });
		pix->SetScale({ 0.7f,0.7f,0.7f });
		cut = 1;
		break;
	case 1:
		if (player->GetPos().x >= 730)
		{
			cut = 2;
		}
		break;
	case 2:
		pre = NewGO < prefab::CSkinModelRender>(0);
		pre->Init(L"modelData/pixie/pixie.cmo",pix_anic,pix_num);
		pre->SetShadowCasterFlag(true);
		pre->SetShadowReceiverFlag(true);
		pix = NewGO<opChara>(0, "pix");
		pix->init(pre, CVector3::Zero);
		v.Set(0, 0, Random().GetRandDouble() * 500 * ((Random().GetRandDouble() > 0.5f) ? -1 : 1));
		pix->SetPos(v);
		v.Set(3 + Random().GetRandDouble() * 6, 0, 0);
		pix->SetMove(v);
		pix->SetScale({ 0.7f,0.7f,0.7f });
		pix->chenGo();

		pix->playAnim(pix_walk);

		pixies.push_back(pix);
		if (time < 5)
		{
			time += GameTime().GetFrameDeltaTime();
		}
		else
		{
			time = 0;
			cut = 3;
		}
		
		break;
	case 3:
		if (first)
		{
			fade->StartFadeOut();
			first = false;
		}
		else
		{
			if (!fade->IsFade())
			{
				first = true;
				state = up;
				cut = 0;
			}
		}
		break;
	}
}

void Opening::SUp()
{
	CVector3 v;
	prefab::CSkinModelRender* gr;
	switch (cut)
	{
	case 0:
		level.AllClear();
		
		fade->StartFadeIn();
		v = player->GetPos();
		v.y = 2000;
		v.x += -10;
		MainCamera().SetPosition(v);
		v.x += -1;
		v.y = 0.5f;
		MainCamera().SetTarget(v);
		MainCamera().Update();
		gr = NewGO < prefab::CSkinModelRender>(0, "gro");
		gr->Init(L"modelData/op/Ground.cmo");
		gr->SetPosition(v);
		gr->SetScale({ 10,10,10 });
		cut = 1;
		break;
	case 1:
		if (time > 3)
		{
			if (first)
			{
				fade->StartFadeOut();
				first = false;
			}
			else
			{
				if (!fade->IsFade())
				{
					first = true;
					time = 0;
					state = front;
					cut = 0;
				}
			}
		}
		else
		{
			time += GameTime().GetFrameDeltaTime();
		}
		break;
	}
}

void Opening::SFront()
{
	CVector3 v;
	switch (cut)
	{
	case 0:
		DeleteGO(FindGO<prefab::CSkinModelRender>("gro"));

		fade->StartFadeIn();
		v = MainCamera().GetPosition();
		v.x += 500;
		v.y = 0.5f;
		MainCamera().SetPosition(v);
		v.y = 10;
		v.x += -50;
		MainCamera().SetTarget(v);
		MainCamera().SetUpdateProjMatrixFunc(CCamera::enUpdateProjMatrixFunc_Perspective);
		MainCamera().Update();

		v = player->GetPos();
		v.x -= 500;
		level.Init(L"level/LopUp.tkl", [&](auto &obj)->bool
		{
			obj.position *= 2;
			obj.position += v;
			obj.scale *= 2;
			return false;
		});

		cut = 1;
		break;
	case 1:
		if (time > 5)
		{
			if (first)
			{
				fade->StartFadeOut();
				first = false;
			}
			else
			{
				if (!fade->IsFade())
				{
					first = true;
					time = 0;
					state = end;
					cut = 0;
				}
			}
		}
		else
		{
			time += GameTime().GetFrameDeltaTime();
		}
		break;
	}
}

void Opening::SEnd()
{
	if (!fade->IsFade())
	{
		NewGO<Title>(0, "title");


		DeleteGO(this);
	}
}
