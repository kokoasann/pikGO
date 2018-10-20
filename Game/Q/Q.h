#pragma once
#include "tkEngine/physics/tkPhysicsStaticObject.h"
class Q :public IGameObject
{
public:
	~Q();
	bool Start();
	void Update();

	CMatrix GetMatrix()
	{
		CMatrix mtscal,mtrota,mtmove,mat;
		mtscal.MakeScaling({ 1,1,1 });
		mtrota.MakeRotationFromQuaternion(CQuaternion::Identity);
		mtmove.MakeTranslation(pos);
		mat.Multiply(mtscal, mtrota);
		mat.Multiply(mat, mtmove);
		return mat;
	}
	CVector3 GetPos()
	{
		return pos;
	}
	void SetPos(CVector3 v);
private:
	prefab::CSkinModelRender* sr;
	CVector3 pos = CVector3::Zero;
	CPhysicsStaticObject pso;
};