#include "stdafx.h"
#include "Timer.h"

Timer::~Timer()
{
}

bool Timer::Start()
{
	watch = NewGO<prefab::CSpriteRender>(0);
	watch->Init(L"sprite/timer/timer.dds", 200, 200);
	watch->SetPosition({ 480,240,0 });

	hand = NewGO<prefab::CSpriteRender>(0);
	float x = 29.0f * 0.2785515320334262f;
	float y = 319.0f * 0.2785515320334262f;
	hand->Init(L"sprite/timer/hand.dds", x, y);
	hand->SetPivot({ 0.5f,0.0f });
	hand->SetPosition({ 480,240,0 });
	return true;
}

void Timer::Update()
{
	time += GameTime().GetFrameDeltaTime();
	float c = time / limit * 360;
	rot.SetRotationDeg(CVector3::AxisZ, c);
	hand->SetRotation(rot);
}

void Timer::PostRender(CRenderContext & rc)
{
	/*font.Begin(rc);
	wchar_t text[256];
	swprintf_s(text, L"time:%f", time);
	font.Draw(text, { 0,0 });
	font.End(rc);*/
}
