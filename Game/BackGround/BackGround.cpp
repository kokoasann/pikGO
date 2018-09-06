#include "stdafx.h"
#include "BackGround.h"
#include "Player.h"

BackGround::~BackGround()
{
}

bool BackGround::Start()
{
	
	CVector3 pos;
	int x, y,cnt = 0;

	x = Random().GetRandDouble() * 28 +1;
	y = Random().GetRandDouble() * 28 +1;
	map[x][y] = 10;

	{
		//CPhysicsStaticObject pso;
		start = NewGO<prefab::CSkinModelRender>(0);
		start->Init(L"modelData/map/start.cmo");
		pos.Set((float)(x * 1000), 0, (float)(y * 1000));
		start->SetPosition(pos);

		//pso.CreateMeshObject(start, pos, CQuaternion::Identity, CVector3::One);
		psoa[cnt].CreateMeshObject(start, pos, CQuaternion::Identity, CVector3::One);
		cnt++;
		//psolist.push_back(pso);

		FindGO<Player>("player")->Setpos(pos);
	}
	CQuaternion enro;
	for (int root = 0; root < 30; root++)
	{
		CQuaternion rot;
		int c,ex = 0,r,count = 0;
		do
		{
			c = 0;
			r = Random().GetRandDouble() * 3;
			switch (r)
			{
			case 0:
				if (x - 1 != 0 && map[x - 1][y] == 0)
				{
					if(root == 0)
					{
						//CQuaternion rot;
						rot.SetRotationDeg(CVector3::AxisY, 180);
						start->SetRotation(rot);
					}
					else if (root == 29)
					{
						enro = CQuaternion::Identity;
					}
					x--;
					map[x][y] = 99;
					c++;
				}
				break;
			case 1:
				if (y + 1 != 29 && map[x][y + 1] == 0)
				{
					if (root == 0)
					{
						//CQuaternion rot;
						rot.SetRotationDeg(CVector3::AxisY, -90);
						start->SetRotation(rot);
					}
					else if (root == 29)
					{
						enro.SetRotationDeg(CVector3::AxisY,90);
					}
					y++;
					map[x][y] = 99;
					c++;
				}
				break;
			case 2:
				if (x + 1 != 29 && map[x + 1][y] == 0)
				{
					if (root == 0)
					{
						//CQuaternion rot = CQuaternion::Identity;
						start->SetRotation(rot);
					}
					else if (root == 29)
					{
						enro.SetRotationDeg(CVector3::AxisY, 90);
					}
					x++;
					map[x][y] = 99;
					c++;
				}
				break;
			case 3:
				if (y - 1 != 0 && map[x][y - 1] == 0)
				{
					if (root == 0)
					{
						//CQuaternion rot;
						rot.SetRotationDeg(CVector3::AxisY, 90);
						start->SetRotation(rot);
					}
					else if (root == 29)
					{
						enro.SetRotationDeg(CVector3::AxisY, -90);
					}
					y--;
					map[x][y] = 99;
					c++;
				}
				break;
			}
			if (c == 0)
			{
				if (count >= 8)
				{
					switch (r)
					{
					case 0:
						if (map[x - 1][y] == 99)
						{
							if (root == 0)
							{
								//CQuaternion rot;
								rot.SetRotationDeg(CVector3::AxisY, 180);
								start->SetRotation(rot);
							}
							else if (root == 29)
							{
								enro = CQuaternion::Identity;
							}
							x--;
							c++;
							ex++;
						}
						break;
					case 1:
						if (map[x][y + 1] == 99)
						{
							if (root == 0)
							{
								//CQuaternion rot;
								rot.SetRotationDeg(CVector3::AxisY, -90);
								start->SetRotation(rot);
							}
							else if (root == 29)
							{
								enro.SetRotationDeg(CVector3::AxisY, 90);
							}
							y++;
							c++;
							ex++;
						}
						break;
					case 2:
						if (map[x + 1][y] == 99)
						{
							if (root == 0)
							{
								//CQuaternion rot = CQuaternion::Identity;
								start->SetRotation(rot);
							}
							else if (root == 29)
							{
								enro.SetRotationDeg(CVector3::AxisY, 90);
							}
							x++;
							c++;
							ex++;
						}
						break;
					case 3:
						if (map[x][y - 1] == 99)
						{
							if (root == 0)
							{
								//CQuaternion rot;
								rot.SetRotationDeg(CVector3::AxisY, 90);
								start->SetRotation(rot);
							}
							else if (root == 29)
							{
								enro.SetRotationDeg(CVector3::AxisY, -90);
							}
							y--;
							c++;
							ex++;
						}
						break;
					}
				}
				else
				{
					count++;
				}
			}
		} while (c == 0);
		if (ex == 0)
		{
			prefab::CSkinModelRender* sr = NewGO<prefab::CSkinModelRender>(0);
			sr->Init(L"modelData/map/tile.cmo");
			pos.Set((float)(x * 1000), 0, (float)(y * 1000));
			sr->SetPosition(pos);

			psoa[cnt].CreateMeshObject(sr, pos, rot, CVector3::One);
			cnt++;
		}
		
	}
	/*do
	{
		x = Random().GetRandDouble() * 29;
		y = Random().GetRandDouble() * 29;
	} while (map[x][y] != 0);*/
	map[x][y] = 20;
	{
		//CPhysicsStaticObject pso;
		end = NewGO<prefab::CSkinModelRender>(0);
		end->Init(L"modelData/map/end.cmo");
		pos.Set((float)(x * 1000), 0, (float)(y * 1000));
		end->SetPosition(pos);
		end->SetRotation(enro);

		psoa[cnt].CreateMeshObject(end, pos, enro, CVector3::One);
		cnt++;
		//pso.CreateMeshObject(end, pos, CQuaternion::Identity, CVector3::One);
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

		psoa[cnt].CreateMeshObject(smr, pos, CQuaternion::Identity, CVector3::One);
		cnt++;
		//CPhysicsStaticObject pso;
		//pso.CreateMeshObject(smr, pos, CQuaternion::Identity, CVector3::One);
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

		psoa[cnt].CreateMeshObject(smr, pos, rot, CVector3::One);
		cnt++;
		//CPhysicsStaticObject pso;
		//pso.CreateMeshObject(smr, pos, CQuaternion::Identity, CVector3::One);
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

		psoa[cnt].CreateMeshObject(smr, pos, CQuaternion::Identity, CVector3::One);
		cnt++;
		//CPhysicsStaticObject pso;
		//pso.CreateMeshObject(smr, pos, CQuaternion::Identity, CVector3::One);
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

		psoa[cnt].CreateMeshObject(smr, pos, rot, CVector3::One);
		cnt++;
		//CPhysicsStaticObject pso;
		//pso.CreateMeshObject(smr, pos, CQuaternion::Identity, CVector3::One);
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

			psoa[cnt].CreateMeshObject(smr, pos, rot, CVector3::One);
			cnt++;
			//CPhysicsStaticObject pso;
			//pso.CreateMeshObject(smr, pos, CQuaternion::Identity, CVector3::One);
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

			psoa[cnt].CreateMeshObject(smr, pos, rot, CVector3::One);
			cnt++;
			//CPhysicsStaticObject pso;
			//pso.CreateMeshObject(smr, pos, CQuaternion::Identity, CVector3::One);
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

			psoa[cnt].CreateMeshObject(smr, pos, CQuaternion::Identity, CVector3::One);
			cnt++;
			//CPhysicsStaticObject pso;
			//pso.CreateMeshObject(smr, pos, CQuaternion::Identity, CVector3::One);
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

			psoa[cnt].CreateMeshObject(smr, pos, rot, CVector3::One);
			cnt++;
			//CPhysicsStaticObject pso;
			//pso.CreateMeshObject(smr, pos, CQuaternion::Identity, CVector3::One);
			//psolist.push_back(pso);
		}
	}
	CQuaternion rot;
	int num;
	for (int xi = 1; xi < 29; xi++)
	{
		for (int yi = 1; yi < 29; yi++)
		{
			if (map[xi][yi] == 0)
			{
				prefab::CSkinModelRender* smr = nullptr;
				int r = round(Random().GetRandDouble());
				r = 0;
				switch (r)
				{
				case 0:
					num = (r+1) * 10;

					//prefab::CSkinModelRender* smr = nullptr;
					smr = NewGO<prefab::CSkinModelRender>(0);
					smr->Init(L"modelData/map/right.cmo");
					pos.Set((float)(xi * 1000), 0, (float)(yi * 1000));
					smr->SetPosition(pos);
					r = Random().GetRandDouble() * 3;
					num += r;
					//CQuaternion rot;
					rot.SetRotationDeg(CVector3::AxisY, 90*r);
					smr->SetRotation(rot);

					maps.push_back(smr);
					
					map[xi][yi] = num;
					break;
				case 3:
					num = (r + 1) * 10;

					//prefab::CSkinModelRender* smr = nullptr;
					smr = NewGO<prefab::CSkinModelRender>(0);
					smr->Init(L"modelData/map/rightkarb.cmo");
					pos.Set((float)(xi * 1000), 0, (float)(yi * 1000));
					smr->SetPosition(pos);
					r = Random().GetRandDouble() * 3;
					num += r;
					//CQuaternion rot;
					rot.SetRotationDeg(CVector3::AxisY, 90 * r);
					smr->SetRotation(rot);

					maps.push_back(smr);

					map[xi][yi] = num;
					break;
				case 2:
					num = (r + 1) * 10;

					//prefab::CSkinModelRender* smr = nullptr;
					smr = NewGO<prefab::CSkinModelRender>(0);
					smr->Init(L"modelData/map/leftkarb.cmo");
					pos.Set((float)(xi * 1000), 0, (float)(yi * 1000));
					smr->SetPosition(pos);
					r = Random().GetRandDouble() * 3;
					num += r;
					//CQuaternion rot;
					rot.SetRotationDeg(CVector3::AxisY, 90 * r);
					smr->SetRotation(rot);

					maps.push_back(smr);

					map[xi][yi] = num;
					break;
				case 1:
					num = (r + 1) * 10;

					
					smr = NewGO<prefab::CSkinModelRender>(0);
					smr->Init(L"modelData/map/road.cmo");
					pos.Set((float)(xi * 1000), 0, (float)(yi * 1000));
					smr->SetPosition(pos);
					r = Random().GetRandDouble() * 3;
					num += r;
					//CQuaternion rot;
					rot.SetRotationDeg(CVector3::AxisY, 90 * r);
					smr->SetRotation(rot);

					maps.push_back(smr);

					map[xi][yi] = num;
					break;
				}
				psoa[cnt].CreateMeshObject(smr, pos, rot, CVector3::One);
				cnt++;
			}
		}
	}

	
	
	return true;
}

void BackGround::Update()
{
}
