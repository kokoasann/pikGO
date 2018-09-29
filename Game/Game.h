#pragma once

#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
#include "tkEngine/character/tkCharacterController.h"
class BackGround;
class Loading;
class PixieSpawner;
class EnemySpawner;
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
	EnInitStep initStep = enInitStep_00;
	prefab::CSpriteRender* point = nullptr;
	prefab::CSpriteRender* o = nullptr;
	CQuaternion oRot = CQuaternion::Identity;
	int T = 30, Y = 30;
	BackGround* bg;
	Loading* lod;
	PixieSpawner* ps;
	EnemySpawner* es;
	prefab::CSkinModelRender* sr;
	//prefab::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
};

