#include "stdafx.h"
#include "Fade.h"


Fade::Fade()
{
}
Fade::~Fade()
{
}

bool Fade::Start()
{
	texture.CreateFromDDSTextureFromFile(L"sprite/fade.dds");
	//sprite.Init(texture, GraphicsEngine().Get2DSpaceScreenWidth(), GraphicsEngine().Get2DSpaceScreenHeight());
	sprite.Init(texture, 1280.0f, 720.0f);
	return true;
}
void Fade::Update()
{
	switch (fade)
	{
	case fadeIn:
		Alpha -= fadeSpeed * GameTime().GetFrameDeltaTime();
		if (Alpha <= 0.0f)
		{
			Alpha = 0.0f;
			fade = fadeIdle;
		}
		break;
	case fadeOut:
		Alpha += fadeSpeed * GameTime().GetFrameDeltaTime();
		if (Alpha >= 1.0f)
		{
			Alpha = 1.0f;
			fade = fadeIdle;
		}
		break;
	case fadeIdle:
		break;
	}
}
void Fade::PostRender(CRenderContext& rc)
{
	if (Alpha > 0.0f)
	{
		sprite.SetMulColor({ 1.0f,1.0f,1.0f,Alpha });
		sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
	}
}