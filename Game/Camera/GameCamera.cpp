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
	pos = toto + player->Getpos();
	pos.y = 80;
	MainCamera().SetPosition(pos);
	tar = tota + player->Getpos();
	tar.y = 80;
	MainCamera().SetTarget(tar);

	camera = &MainCamera();
	CCS.Init(5.0f);
	//CCC.Init(5.0f, 5.0f, pos);
	//ばねカメラの初期化。
	//Scamera.Init(
	//	MainCamera(),		//ばねカメラの処理を行うカメラを指定する。
	//	1000000.0f,			//カメラの移動速度の最大値。
	//	true,				//カメラと地形とのあたり判定を取るかどうかのフラグ。trueだとあたり判定を行う。
	//	5.0f				//カメラに設定される球体コリジョンの半径。第３引数がtrueの時に有効になる。
	//);
	//camera.Update();
	MainCamera().Update();
	return true;
}

void GameCamera::Update()
{
	//注視点を計算する。
	CVector3 target = player->Getpos();
	//プレイヤの足元からちょっと上を注視点とする。
	target.y += 80.0f;
	CVector3 old = pos;
	CVector3 oldt = tar;
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
	if (toPosDir.y < -0.9f) {
		//カメラが上向きすぎ。
		toto = toCameraPosOld;
		tota = toCameraTarOld;
	}
	else if (toPosDir.y > 0.9f) {
		//カメラが下向きすぎ。
		toto = toCameraPosOld;
		tota = toCameraTarOld;
	}

	//視点を計算する。
	CVector3 nt = toto,ot = toto;
	nt.Normalize();
	toto += (nt * Pad(0).GetWheel() * 20);
	if (toto.Length() < 158.0f)
		toto = ot;

	pos = target + toto;
	tar = target + tota;

	//CVector3 mop = posr - old;
	//CVector3 mot = tarr - oldt;

	//pos = old + mop * GameTime().GetFrameDeltaTime();
	//tar = oldt + mot * GameTime().GetFrameDeltaTime();
	//pos += player->GetMove();
	//tar += player->GetMove();

	CVector3 res,re;
	//CCS.Execute(res, pos, old);
	res = CCS.Execute(pos, old);
	
	CCS.Execute(re, res, target);
	//re = CCS.Execute(target,res);
	//CVector3 move = pos - old;
	//pos = CCC.Execute(GameTime().GetFrameDeltaTime(),move);
	pos = re;
	MainCamera().SetPosition(pos);
	MainCamera().SetTarget(tar);
	MainCamera().Update();
}
