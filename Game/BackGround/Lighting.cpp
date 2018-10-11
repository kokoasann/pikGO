#include "stdafx.h"
#include "Lighting.h"
#include "tkEngine/light/tkDirectionLight.h"

Lighting::~Lighting()
{
	for (auto light : lights)
	{
		DeleteGO(light);
	}
}

bool Lighting::Start()
{
	CVector3 pos;

	prefab::CDirectionLight* light = NewGO<prefab::CDirectionLight>(0);
	pos.Set(0.707f, -0.707f, 0.0f);
	light->SetDirection(pos);
	light->SetColor({ 100.0f,100.0f,100.0f,1.0f });
	lights.push_back(light);
	poss.push_back(pos);


	light = NewGO<prefab::CDirectionLight>(0);
	pos.Set(-0.707f, -0.707f, 0.0f);
	light->SetDirection(pos);
	light->SetColor({ 50.0f,50.0f,80.0f,1.0f });
	lights.push_back(light);
	poss.push_back(pos);

	
	light = NewGO<prefab::CDirectionLight>(0);
	pos.Set(0.0f, 0.207f, 0.707f);
	light->SetDirection(pos);
	light->SetColor({ 37.5f,60.0f,55.5f,0.7f });
	lights.push_back(light);
	poss.push_back(pos);


	light = NewGO<prefab::CDirectionLight>(0);
	pos.Set(0.707f, 0.207f, -0.707f);
	light->SetDirection(pos);
	light->SetColor({ 37.5f,60.0f,55.5f,0.7f });
	lights.push_back(light);
	poss.push_back(pos);


	light = NewGO<prefab::CDirectionLight>(0);
	pos.Set(0.0f, 1.0f, 0.0f);
	light->SetDirection(pos);
	light->SetColor({ 2.31f,60.0f,25.5f,0.5f });
	lights.push_back(light);
	poss.push_back(pos);
	return true;
}

void Lighting::Update()
{
}
