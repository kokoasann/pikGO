#include "stdafx.h"
#include "Camera/GameCamera.h"
#include "Player.h"
#include "tkEngine/light/tkDirectionLight.h"

GameCamera::~GameCamera()
{

}

bool GameCamera::Start()
{
	//�����_���王�_�܂ł̃x�N�g����ݒ�B
	//pos.Set(0.0f, 50.0f, 100.0f);

	toto.Set(-50.0f, 0.0f, 150);
	tota.Set(-50.0f, 0.0f, -150);
	//�v���C���[�̃C���X�^���X��T���B
	player = FindGO<Player>("player");

	//�J�����̃j�A�N���b�v�ƃt�@�[�N���b�v��ݒ肷��B
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
	//�΂˃J�����̏������B
	//Scamera.Init(
	//	MainCamera(),		//�΂˃J�����̏������s���J�������w�肷��B
	//	1000000.0f,			//�J�����̈ړ����x�̍ő�l�B
	//	true,				//�J�����ƒn�`�Ƃ̂����蔻�����邩�ǂ����̃t���O�Btrue���Ƃ����蔻����s���B
	//	5.0f				//�J�����ɐݒ肳��鋅�̃R���W�����̔��a�B��R������true�̎��ɗL���ɂȂ�B
	//);
	//camera.Update();
	MainCamera().Update();
	return true;
}

void GameCamera::Update()
{
	//�����_���v�Z����B
	CVector3 target = player->Getpos();
	//�v���C���̑������炿����Ə�𒍎��_�Ƃ���B
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
	
	//�p�b�h�̓��͂��g���ăJ�������񂷁B
	float x = Pad(0).GetRStickXF();
	
	float y = Pad(0).GetRStickYF();

	
	//Y������̉�]
	CQuaternion qRot,qta;
	qRot.SetRotationDeg(CVector3::AxisY, 2.0f * x);
	qRot.Multiply(toto);

	qta.SetRotationDeg(CVector3::AxisY, 2.0f * x);
	qta.Multiply(tota);

	CVector3 toCameraPosOld = toto;
	CVector3 toCameraTarOld = tota;
	//X������̉�]�B
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
	//�J�����̉�]�̏�����`�F�b�N����B
	//�����_���王�_�܂ł̃x�N�g���𐳋K������B
	//���K������ƁA�x�N�g���̑傫�����P�ɂȂ�B
	//�傫�����P�ɂȂ�Ƃ������Ƃ́A�x�N�g�����狭�����Ȃ��Ȃ�A�����݂̂̏��ƂȂ�Ƃ������ƁB
	CVector3 toPosDir = toto;
	toPosDir.Normalize();
	if (toPosDir.y < -0.9f) {
		//�J����������������B
		toto = toCameraPosOld;
		tota = toCameraTarOld;
	}
	else if (toPosDir.y > 0.9f) {
		//�J�����������������B
		toto = toCameraPosOld;
		tota = toCameraTarOld;
	}

	//���_���v�Z����B
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
