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
	//pos.Set(0.0f, 50.0f, 100.0f);

	pos.Set(0, 70, 200);
	toto.Set(0.0f, 50.0f, 180.0f);
	//プレイヤーのインスタンスを探す。
	player = FindGO<Player>("player");

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
	Scamera.SetPosition(pos);
	//camera.Update();
	return true;
}

void GameCamera::Update()
{
	//注視点を計算する。
	CVector3 target = player->pos;
	//プレイヤの足元からちょっと上を注視点とする。
	target.y += 50.0f;

	CVector3 toCameraPosOld = toto;
	//パッドの入力を使ってカメラを回す。
	float x = Pad(0).GetRStickXF();
	float y = Pad(0).GetRStickYF();
	//Y軸周りの回転
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY, 2.0f * x);
	qRot.Multiply(toto);
	//X軸周りの回転。
	CVector3 axisX;
	axisX.Cross(CVector3::AxisY, toto);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 2.0f * y);
	qRot.Multiply(toto);
	//カメラの回転の上限をチェックする。
	//注視点から視点までのベクトルを正規化する。
	//正規化すると、ベクトルの大きさが１になる。
	//大きさが１になるということは、ベクトルから強さがなくなり、方向のみの情報となるということ。
	CVector3 toPosDir = toto;
	toPosDir.Normalize();
	if (toPosDir.y < -0.5f) {
		//カメラが上向きすぎ。
		toto = toCameraPosOld;
	}
	else if (toPosDir.y > 0.8f) {
		//カメラが下向きすぎ。
		toto = toCameraPosOld;
	}

	//視点を計算する。
	CVector3 pos = target + toto;

	//pos += player->GetMove();
	//tar += player->GetMove();
	Scamera.SetPosition(pos);
	Scamera.SetTarget(target);

	Scamera.Update();
}
