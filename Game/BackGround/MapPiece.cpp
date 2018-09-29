#include "stdafx.h"
#include "MapPiece.h"

bool MapPiece::Start()
{
	return true;
}

void MapPiece::Update()
{
	
}

void MapPiece::init(CVector3 pos, CQuaternion rot,int m)
{
	this->pos = pos;
	this->rot = rot;
	model = m;
	//pso.CreateMeshObject(sr, pos, rot,CVector3::One);
}

void MapPiece::Create()
{
	sr = NewGO < prefab::CSkinModelRender>(0);

	switch (model)
	{
	case 0:
		sr->Init(L"modelData/map/start.cmo");
		break;
	case 1:
		sr->Init(L"modelData/map/end.cmo");
		break;
	case 2:
		sr->Init(L"modelData/map/tile.cmo");
		break;
	case 3:
		sr->Init(L"modelData/map/right.cmo");
		break;
	case 4:
		sr->Init(L"modelData/map/leftkarb.cmo");
		break;
	case 5:
		sr->Init(L"modelData/map/rightkarb.cmo");
		break;
	}
	sr->SetPosition(pos);
	sr->SetRotation(rot);

	initPhysic();
}

void MapPiece::initPhysic()
{
	pso.CreateMeshObject(sr, pos, rot, CVector3::One);
}

void MapPiece::SetPos(CVector3 pos)
{
	this->pos = pos;
	//sr->SetPosition(pos);
	//pso.CreateMeshObject(sr, pos, rot, CVector3::One);
}

void MapPiece::SetRot(CQuaternion rot)
{
	this->rot = rot;
	//sr->SetRotation(rot);
	//pso.CreateMeshObject(sr, pos, rot, CVector3::One);
}
