#include "stdafx.h"
#include "BackGround.h"

BackGround::~BackGround()
{
}

bool BackGround::Start()
{
	
	CVector3 pos;
	int x, y;
	x = Random().GetRandDouble() * 30;
	y = Random().GetRandDouble() * 30;
	map[x][y] = 10;

	{
		CPhysicsStaticObject pso;
		start = NewGO<prefab::CSkinModelRender>(0);
		start->Init(L"modelData/map/start.cmo");
		pos.Set((float)(x * 1000), 0, (float)(y * 1000));
		start->SetPosition(pos);

		pso.CreateMeshObject(start, pos, CQuaternion::Identity, CVector3::One);
		//psolist.push_back(pso);
	}
	
	do
	{
		x = Random().GetRandDouble() * 30;
		y = Random().GetRandDouble() * 30;
	} while (map[x][y] != 0);
	map[x][y] = 20;
	{
		CPhysicsStaticObject pso;
		end = NewGO<prefab::CSkinModelRender>(0);
		end->Init(L"modelData/map/end.cmo");
		pos.Set((float)(x * 1000), 0, (float)(y * 1000));
		end->SetPosition(pos);

		pso.CreateMeshObject(end, pos, CQuaternion::Identity, CVector3::One);
		//psolist.push_back(pso);
	}

	if (map[0][0] = 0)
	{
		prefab::CSkinModelRender* smr = nullptr;
		smr = NewGO<prefab::CSkinModelRender>(0);
		pos.Set(0, 0, 0);
		smr->Init(L"modelData/map/rightkarb.cmo");
		smr->SetPosition({ 0,0,0});
		maps.push_back(smr);
		map[0][0] = 30;

		CPhysicsStaticObject pso;
		pso.CreateMeshObject(smr, pos, CQuaternion::Identity, CVector3::One);
		//psolist.push_back(pso);
	}
	if (map[0][29] == 0)
	{
		prefab::CSkinModelRender* smr = nullptr;
		smr = NewGO<prefab::CSkinModelRender>(0);

		smr = NewGO<prefab::CSkinModelRender>(0);
		smr->Init(L"modelData/map/rightkarb.cmo");
		pos.Set(0, 0, (float)(29 * 1000));
		smr->SetPosition(pos);
		CQuaternion rot;
		rot.SetRotationDeg(CVector3::AxisY, 180);
		smr->SetRotation(rot);
		maps.push_back(smr);
		map[0][29] = 33;

		CPhysicsStaticObject pso;
		pso.CreateMeshObject(smr, pos, CQuaternion::Identity, CVector3::One);
		//psolist.push_back(pso);
	}

	if (map[29][0] == 0)
	{
		prefab::CSkinModelRender* smr = nullptr;
		smr = NewGO<prefab::CSkinModelRender>(0);

		smr->Init(L"modelData/map/leftkarb.cmo");
		pos.Set((float)(29 * 1000), 0, 0);
		smr->SetPosition(pos);
		maps.push_back(smr);
		map[29][0] = 40;

		CPhysicsStaticObject pso;
		pso.CreateMeshObject(smr, pos, CQuaternion::Identity, CVector3::One);
		//psolist.push_back(pso);
	}
	if (map[29][29] == 0)
	{
		prefab::CSkinModelRender* smr = nullptr;
		smr = NewGO<prefab::CSkinModelRender>(0);

		smr = NewGO<prefab::CSkinModelRender>(0);
		smr->Init(L"modelData/map/leftkarb.cmo");
		pos.Set((float)(0 * 1000), 0, (float)(29 * 1000));
		smr->SetPosition(pos);
		CQuaternion rot;
		rot.SetRotationDeg(CVector3::AxisY, 180);
		smr->SetRotation(rot);
		maps.push_back(smr);
		map[29][29] = 43;

		CPhysicsStaticObject pso;
		pso.CreateMeshObject(smr, pos, CQuaternion::Identity, CVector3::One);
		//psolist.push_back(pso);
	}

	x = 0;
	y = 0;
	for(x = 1; x < 29;x++)
	{
		
		if (map[x][0] == 0)
		{
			prefab::CSkinModelRender* smr = nullptr;
			smr = NewGO<prefab::CSkinModelRender>(0);

			smr->Init(L"modelData/map/right.cmo");
			pos.Set((float)(x * 1000), 0, 0);
			smr->SetPosition({ (float)(x * 1000),0,0});
			CQuaternion rot;
			rot.SetRotationDeg(CVector3::AxisY, -90);
			smr->SetRotation(rot);

			maps.push_back(smr);
			map[x][0] = 40;

			CPhysicsStaticObject pso;
			pso.CreateMeshObject(smr, pos, CQuaternion::Identity, CVector3::One);
			//psolist.push_back(pso);
		}
		if (map[x][29] == 0)
		{
			prefab::CSkinModelRender* smr = nullptr;
			smr = NewGO<prefab::CSkinModelRender>(0);

			smr = NewGO<prefab::CSkinModelRender>(0);
			smr->Init(L"modelData/map/right.cmo");
			pos.Set((float)(x * 1000), 0, (float)(29 * 1000));
			smr->SetPosition(pos);
			CQuaternion rot;
			rot.SetRotationDeg(CVector3::AxisY, 90);
			smr->SetRotation(rot);

			maps.push_back(smr);
			map[x][29] = 43;

			CPhysicsStaticObject pso;
			pso.CreateMeshObject(smr, pos, CQuaternion::Identity, CVector3::One);
			//psolist.push_back(pso);
		}
		
	}

	for (y = 1; y < 29; y++)
	{
		if (map[0][y] == 0)
		{
			prefab::CSkinModelRender* smr = nullptr;
			smr = NewGO<prefab::CSkinModelRender>(0);
			smr->Init(L"modelData/map/right.cmo");
			pos.Set(0, 0, (float)(y * 1000));
			smr->SetPosition(pos);

			maps.push_back(smr);
			map[0][y] = 40;

			CPhysicsStaticObject pso;
			pso.CreateMeshObject(smr, pos, CQuaternion::Identity, CVector3::One);
			//psolist.push_back(pso);
		}

		if (map[29][y] == 0)
		{
			prefab::CSkinModelRender* smr = nullptr;
			smr = NewGO<prefab::CSkinModelRender>(0);
			smr->Init(L"modelData/map/right.cmo");
			pos.Set((float)(29 * 1000), 0, (float)(y * 1000));
			smr->SetPosition(pos);
			CQuaternion rot;
			rot.SetRotationDeg(CVector3::AxisY, 180);
			smr->SetRotation(rot);

			maps.push_back(smr);
			map[29][y] = 43;

			CPhysicsStaticObject pso;
			pso.CreateMeshObject(smr, pos, CQuaternion::Identity, CVector3::One);
			//psolist.push_back(pso);
		}
	}

	for (int xi = 0; xi < 30; xi++)
	{
		for (int yi = 0; yi < 30; yi++)
		{
			if (map[xi][yi] == 0)
			{

			}
		}
	}

	
	
	return true;
}

void BackGround::Update()
{
}
