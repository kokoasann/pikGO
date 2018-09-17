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

	toto.Set(-50.0f, 0.0f, 150);
	tota.Set(-50.0f, 0.0f, -150);
	//プレイヤーのインスタンスを探す。
	player = FindGO<Player>("player");

	//カメラのニアクリップとファークリップを設定する。
	MainCamera().SetNear(1.0f);
	MainCamera().SetFar(50000.0f);

	camera = &MainCamera();
	CCS.Init(5.0f);

	//ばねカメラの初期化。
	Scamera.Init(
		MainCamera(),		//ばねカメラの処理を行うカメラを指定する。
		1000000.0f,			//カメラの移動速度の最大値。
		true,				//カメラと地形とのあたり判定を取るかどうかのフラグ。trueだとあたり判定を行う。
		5.0f				//カメラに設定される球体コリジョンの半径。第３引数がtrueの時に有効になる。
	);
	//camera.Update();
	return true;
}

void GameCamera::Update()
{
	//注視点を計算する。
	CVector3 target = player->Getpos();
	//プレイヤの足元からちょっと上を注視点とする。
	target.y += 80.0f;

	/*CVector3 camX = Scamera.GetCamera()->GetForward();
	camX.y = 0;
	camX.Normalize();
	target += camX*20;*/

	/*CVector3 plv = player->GetMove();
	plv.Cross(CVector3::AxisY,plv);
	plv.Normalize();
	plv *= 40;
	target += plv;*/
	CVector3 pt = toto,tt = tota;
	
	//パッドの入力を使ってカメラを回す。
	float x = Pad(0).GetRStickXF();
	
	float y = Pad(0).GetRStickYF();

	
	//Y軸周りの回転
	CQuaternion qRot,qta;
	qRot.SetRotationDeg(CVector3::AxisY, 2.0f * x);
	qRot.Multiply(toto);

	qta.SetRotationDeg(CVector3::AxisY, 2.0f * x);
	qta.Multiply(tota);

	CVector3 toCameraPosOld = toto;
	CVector3 toCameraTarOld = tota;
	//X軸周りの回転。
	CVector3 axisX;
	axisX.Cross(CVector3::AxisY, toto);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 2.0f * y);
	qRot.Multiply(toto);

	axisX = CVector3::Zero;
	axisX.Cross(CVector3::AxisY, tota);
	axisX.Normalize();
	qta.SetRotationDeg(axisX, -2.0f * y);
	qta.Multiply(tota);
	//カメラの回転の上限をチェックする。
	//注視点から視点までのベクトルを正規化する。
	//正規化すると、ベクトルの大きさが１になる。
	//大きさが１になるということは、ベクトルから強さがなくなり、方向のみの情報となるということ。
	CVector3 toPosDir = toto;
	toPosDir.Normalize();
	if (toPosDir.y < -0.5f) {
		//カメラが上向きすぎ。
		toto = toCameraPosOld;
		tota = toCameraTarOld;
	}
	else if (toPosDir.y > 0.8f) {
		//カメラが下向きすぎ。
		toto = toCameraPosOld;
		tota = toCameraTarOld;
	}

	//視点を計算する。
	CVector3 nt = toto;
	nt.Normalize();
	toto += (nt * Pad(0).GetWheel() * 2);
	pos = target + toto;
	tar = target + tota;
	//pos += player->GetMove();
	//tar += player->GetMove();

	//Scamera.SetPosition(pos);
	//Scamera.SetTarget(target+tota);
	//Scamera.Update();

	CVector3 res;
	CCS.Execute(res, pos, tar);

	MainCamera().SetPosition(res);
	MainCamera().SetTarget(tar);
	MainCamera().Update();
	
}
