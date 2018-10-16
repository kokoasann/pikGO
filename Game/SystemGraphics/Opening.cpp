#include "stdafx.h"
#include "Opening.h"
#include "opChara.h"
#include "Fade.h"

Opening::~Opening()
{
	DeleteGO(player);
	DeleteGO(pre);
}

bool Opening::Start()
{
	MainCamera().SetPosition({ -250.0f,450.0f,130.0f });
	MainCamera().SetTarget({ 100.0f,0.0f,0.0f });
	MainCamera().SetFar(9999.9f);
	MainCamera().SetNear(1.0f);
	MainCamera().SetViewAngle(20.0f);
	MainCamera().Update();

	CVector3 ppo = { -300.0f,0.0f,500.0f };
	pre = NewGO<prefab::CSkinModelRender>(0);
	pre->Init(L"modelData/unityChan.cmo");
	player = NewGO<opChara>(0, "pla");
	player->init(pre,ppo);
	player->chenGo();
	CVector3 v = ppo * -1;
	v.Normalize();
	v *= 3;
	player->SetMove(v);

	pre = NewGO < prefab::CSkinModelRender>(0);
	pre->Init(L"modelData/pixie/pixie.cmo");
	pix = NewGO<opChara>(0, "pix");
	pix->init(pre, CVector3::Zero);
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
	return true;
}

void Opening::Update()
{
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
		MainCamera().SetPosition({ 800,230,-2000 });
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
		pre->Init(L"modelData/pixie/pixie.cmo");
		pix = NewGO<opChara>(0, "pix");
		pix->init(pre, CVector3::Zero);
		v.Set(0, 0, Random().GetRandDouble() * 500 * ((Random().GetRandDouble() > 0.5f) ? -1 : 1));
		pix->SetPos(v);
		v.Set(3 + Random().GetRandDouble() * 6, 0, 0);
		pix->SetMove(v);
		pix->SetScale({ 0.7f,0.7f,0.7f });
		pix->chenGo();

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
			if (fade->IsFade())
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
	switch (cut)
	{
	case 0:
		fade->StartFadeIn();
		v = player->GetPos();
		v.y = 2000;
		v.x += -10;
		MainCamera().SetPosition(v);
		v.x += -1;
		v.y = 0.5f;
		MainCamera().SetTarget(v);
		MainCamera().Update();
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
				if (fade->IsFade())
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
				if (fade->IsFade())
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
}
