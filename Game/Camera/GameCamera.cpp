#include "stdafx.h"
#include "Camera/GameCamera.h"
#include "Player.h"
#include "tkEngine/light/tkDirectionLight.h"

GameCamera::~GameCamera()
{

}

bool GameCamera::Start()
{
	//注視点から視点までのベクトルを設定。
	pos.Set(0.0f, 50.0f, 100.0f);
	//プレイヤーのインスタンスを探す。
	//m_player = FindGO<Player>("Player");

	//カメラのニアクリップとファークリップを設定する。
	MainCamera().SetNear(1.0f);
	MainCamera().SetFar(10000.0f);

	//ばねカメラの初期化。
	Scamera.Init(
		MainCamera(),		//ばねカメラの処理を行うカメラを指定する。
		1000.0f,			//カメラの移動速度の最大値。
		true,				//カメラと地形とのあたり判定を取るかどうかのフラグ。trueだとあたり判定を行う。
		5.0f				//カメラに設定される球体コリジョンの半径。第３引数がtrueの時に有効になる。
	);
	Scamera.SetTarget({ 0,70,0 });
	Scamera.SetPosition({ 0,70,200 });
	Scamera.Update();
	return true;
}

void GameCamera::Update()
{

}
