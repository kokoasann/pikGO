#pragma once

class opChara :public IGameObject
{
public:
	~opChara();
	bool Start();
	void init(prefab::CSkinModelRender* sr, CVector3 pos);
	void Update();
	bool Rotation();
	void SetPos(CVector3 pos);
	void SetMove(CVector3 v);

	void SetRot(CQuaternion rot);
	void SetRot(float ang);
	void SetRot(CVector3 v);

	void RotaMove();
	void SetRotSpeed(float a)
	{
		rotspeed = a;
	}
	CVector3 GetPos()
	{
		return pos;
	}
	enum State
	{
		idle,
		go,
		rota,
	};
	void chenIdle()
	{
		state = idle;
	}
	void chenGo()
	{
		state = go;
	}
	void chenRota()
	{
		state = rota;
	}

	void SetScale(CVector3 v);
	void playAnim(int num);
private:
	State state = idle;
	prefab::CSkinModelRender* sr;
	CVector3 pos = CVector3::Zero;
	CVector3 move = CVector3::AxisZ;
	CVector3 oldmove = CVector3::AxisZ;
	CQuaternion rot = CQuaternion::Identity;
	float Frot = 0;
	int rotspeed = 1;
	int rotcount = 0;
	bool rotcomp = false;
};