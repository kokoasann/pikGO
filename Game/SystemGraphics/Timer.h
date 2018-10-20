#pragma once

class Timer : public IGameObject
{
public:
	~Timer();
	bool Start();
	void Update();
	void PostRender(CRenderContext& rc) override;
	void setLimit(float lim)
	{
		limit = lim;
	}
private:
	float time = 0.0f;
	float limit = 60.0f;
	CQuaternion rot = CQuaternion::Identity;
	prefab::CSpriteRender* watch;
	prefab::CSpriteRender* hand;
	CFont font;
};