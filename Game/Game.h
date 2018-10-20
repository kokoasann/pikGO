#pragma once

#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
#include "tkEngine/character/tkCharacterController.h"
class Fade;
class Player;
class BackGround;
class Loading;
class PixieSpawner;
class EnemySpawner;
class RootFind;
class Lighting;
class Timer;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void PostRender(CRenderContext& rc) override;
	enum EnInitStep {
		enInitStep_00,
		enInitStep_01,
		enInitStep_02,
	};

	int GetTate()
	{
		return T;
	}
	int GetYoko()
	{
		return Y;
	}

private:
	EnInitStep initStep = enInitStep_00;
	prefab::CSpriteRender* point = nullptr;
	prefab::CSpriteRender* o = nullptr;
	CQuaternion oRot = CQuaternion::Identity;
	int T = 12, Y = 12;

	Player* player;

	BackGround* bg;
	Loading* lod;
	PixieSpawner* ps;
	EnemySpawner* es;

	Lighting* lighting;
	Timer* timer;

	RootFind* RF;
	prefab::CSkinModelRender* sr;
	//prefab::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。

	Fade* fade;
	CFont font;
	int pixieoCount = 0;
	bool Clear = false;
};

