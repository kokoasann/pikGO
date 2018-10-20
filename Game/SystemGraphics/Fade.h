#pragma once
class Fade :public IGameObject
{
public:
	Fade();
	~Fade();
	bool Start();
	void Update();
	void PostRender(CRenderContext& rc);
	void changeBlack();
	void changeWhite();
	void StartFadeIn()
	{
		fade = fadeIn;
	}
	void StartFadeOut()
	{
		fade = fadeOut;
	}
	bool IsFade()const
	{
		return fade != fadeIdle;
	}
	void SetFadeSpeed(float f)
	{
		fadeSpeed = f;
	}

private:
	enum EnState
	{
		fadeIn,
		fadeOut,
		fadeIdle
	};
	CShaderResourceView texture;
	CSprite sprite;
	EnState fade = fadeIdle;
	float Alpha = 1.0f;
	float fadeSpeed = 2.0f;
};

