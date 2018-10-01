#include "stdafx.h"
#include "BackGround.h"
#include "Player.h"
#include "Q/Q.h"
#include "MapPiece.h"


BackGround::~BackGround()
{
	delete map;
	delete initThread;
}

bool BackGround::Start()
{
	return true;
}

void BackGround::init(const int T, const int Y)
{
	initThread = new std::thread([=] {
		CStopwatch sw;
		sw.Start();
		tx = T*3;
		yy = Y*3;
		map = new int*[tx];
		for (int i = 0; i < tx; i++)
		{
			map[i] = new int[yy];
		}
		for (int y = 0; y < tx; y++)
		{
			for (int x = 0; x < yy; x++)
			{
				map[y][x] = 0;
			}
		}

		int** minimap = new int*[T];
		for (int i = 0; i < T; i++)
		{
			minimap[i] = new int[Y];
		}
		for (int y = 0; y < T; y++)
		{
			for (int x = 0; x < Y; x++)
			{
				minimap[y][x] = 0;
			}
		}
		CVector3 pos;
		int x, y, cnt = 0,sx,sy;

		sx = Random().GetRandDouble() * (T - 2) + 1;
		sy = Random().GetRandDouble() * (Y - 2) + 1;
		minimap[sx][sy] = 10;
		x = sx;
		y = sy;
		MapPiece* stm = NewGO<MapPiece>(0);
		{
			pos.Set((float)(x * 1000), 0, (float)(y * 1000));

			stm->init(pos, CQuaternion::Identity, (int)start);
			
			FindGO<Player>("player")->inipo = pos;
		}
		CQuaternion enro;
		int enn = 0;
		int rm = (int)((T + Y) / 2);
		for (int root = 0; root < rm; root++)
		{
			CQuaternion rot;
			int c, ex = 0, r, count = 0;
			do
			{
				c = 0;
				r = Random().GetRandDouble() * 3;
				switch (r)
				{
				case 0:
					if (x - 1 != 0 && minimap[x - 1][y] == 0)
					{
						if (root == 0)
						{
							rot.SetRotationDeg(CVector3::AxisY, 180);
							stm->SetRot(rot);
							PMS.push_back(stm);
							Maping(sx, sy, 2, start);
							//@todo for debug stm->initPhysic();
							cnt++;
						}
						else if (root == rm - 1)
						{
							enro = CQuaternion::Identity;
							enn = 0;
						}
						x--;
						minimap[x][y] = 99;
						Maping(x, y, 0, tile);
						c++;
					}
					break;
				case 1:
					if (y + 1 != Y - 1 && minimap[x][y + 1] == 0)
					{
						if (root == 0)
						{
							rot.SetRotationDeg(CVector3::AxisY, -90);
							stm->SetRot(rot);
							PMS.push_back(stm);
							Maping(sx, sy, 3, start);
							//stm->initPhysic();
							cnt++;
						}
						else if (root == rm - 1)
						{
							enro.SetRotationDeg(CVector3::AxisY, 90);
							enn = 1;
						}
						y++;
						minimap[x][y] = 99;
						Maping(x, y, 0, tile);
						c++;
					}
					break;
				case 2:
					if (x + 1 != T - 1 && minimap[x + 1][y] == 0)
					{
						if (root == 0)
						{
							CQuaternion rot = CQuaternion::Identity;
							stm->SetRot(rot);
							PMS.push_back(stm);
							Maping(sx, sy, 0, start);
					//@todo for debug		stm->initPhysic();
							cnt++;
						}
						else if (root == rm - 1)
						{
							enro.SetRotationDeg(CVector3::AxisY, 90);
							enn = 1;
						}
						x++;
						minimap[x][y] = 99;
						Maping(x, y, 0, tile);
						c++;
					}
					break;
				case 3:
					if (y - 1 != 0 && minimap[x][y - 1] == 0)
					{
						if (root == 0)
						{
							rot.SetRotationDeg(CVector3::AxisY, 90);
							stm->SetRot(rot);
							PMS.push_back(stm);
							Maping(sx, sy, 1, start);
							//stm->initPhysic();
							cnt++;
						}
						else if (root == rm - 1)
						{
							enro.SetRotationDeg(CVector3::AxisY, -90);
							enn = 3;
						}
						y--;
						minimap[x][y] = 99;
						Maping(x, y, 0, tile);
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
							if (minimap[x - 1][y] == 99)
							{
								if (root == 0)
								{
									rot.SetRotationDeg(CVector3::AxisY, 180);
									stm->SetRot(rot);
									PMS.push_back(stm);
									Maping(sx, sy, 2, start);
									//stm->initPhysic();
									cnt++;
								}
								else if (root == rm - 1)
								{
									enro = CQuaternion::Identity;
									enn = 0;
								}
								x--;
								c++;
								ex++;
							}
							break;
						case 1:
							if (minimap[x][y + 1] == 99)
							{
								if (root == 0)
								{
									rot.SetRotationDeg(CVector3::AxisY, -90);
									stm->SetRot(rot);
									PMS.push_back(stm);
									Maping(sx, sy, 3, start);
									//stm->initPhysic();
									cnt++;
								}
								else if (root == rm - 1)
								{
									enro.SetRotationDeg(CVector3::AxisY, 90);
									enn = 1;
								}
								y++;
								c++;
								ex++;
							}
							break;
						case 2:
							if (minimap[x + 1][y] == 99)
							{
								if (root == 0)
								{
									CQuaternion rot = CQuaternion::Identity;
									stm->SetRot(rot);
									PMS.push_back(stm);
									Maping(sx, sy, 0, start);
									//stm->initPhysic();
									cnt++;
								}
								else if (root == rm - 1)
								{
									enro.SetRotationDeg(CVector3::AxisY, 90);
									enn = 0;
								}
								x++;
								c++;
								ex++;
							}
							break;
						case 3:
							if (minimap[x][y - 1] == 99)
							{
								if (root == 0)
								{
									rot.SetRotationDeg(CVector3::AxisY, 90);
									stm->SetRot(rot);
									PMS.push_back(stm);
									Maping(sx, sy, 1, start);
									//stm->initPhysic();
									cnt++;
								}
								else if (root == rm - 1)
								{
									enro.SetRotationDeg(CVector3::AxisY, -90);
									enn = 3;
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
				pos.Set((float)(x * 1000), 0, (float)(y * 1000));

				MapPiece* mp = NewGO<MapPiece>(0);
				mp->init(pos, CQuaternion::Identity, tile);
				//mp->initPhysic();
				PMS.push_back(mp);
				/*prefab::CSkinModelRender* sk = NewGO<prefab::CSkinModelRender>(0);
				sk->Init(L"modelData/pixie/pixie.cmo");
				sk->SetPosition(pos);*/
			}

		}
		minimap[x][y] = 20;
		{
			pos.Set((float)(x * 1000), 0, (float)(y * 1000));
			level.Init(L"level/end.tkl", [&](LevelObjectData &obj)
			{
				if (obj.EqualObjectName(L"end"))
				{
					MapPiece* em = NewGO<MapPiece>(0);
					em->init(pos, enro, end);
					//em->initPhysic();
					PMS.push_back(em);
					Maping(x, y, enn, end);
					return true;
				}
				else if (obj.EqualObjectName(L"Q"))
				{
					/*Q* q = NewGO<Q>(0, "Q");
					CVector3 qp = obj.position;
					qp += pos;
					q->pos = qp;*/
					return true;
				}
				return false;
			});
		}

		if (minimap[0][0] = 0)
		{
			pos.Set(0, 0, 0);

			minimap[0][0] = 30;

			MapPiece* mp = NewGO<MapPiece>(0);
			mp->init(pos, CQuaternion::Identity, Rkarb);
			PMS.push_back(mp);
			Maping(0, 0, 0, Rkarb);
			//mp->initPhysic();
		}
		if (minimap[0][Y - 1] == 0)
		{
			pos.Set(0, 0, (float)((Y - 1) * 1000));

			CQuaternion rot;
			rot.SetRotationDeg(CVector3::AxisY, 180);

			minimap[0][Y - 1] = 33;

			MapPiece* mp = NewGO<MapPiece>(0);
			mp->init(pos, rot, Rkarb);
			PMS.push_back(mp);
			Maping(0, Y - 1, 2,Rkarb);
			//mp->initPhysic();
		}

		if (minimap[T - 1][0] == 0)
		{
			pos.Set((float)((T - 1) * 1000), 0, 0);

			minimap[T - 1][0] = 40;

			MapPiece* mp = NewGO<MapPiece>(0);
			mp->init(pos, CQuaternion::Identity, Lkarb);
			PMS.push_back(mp);
			Maping(T - 1, 0, 0, Lkarb);
			//mp->initPhysic();
		}
		if (minimap[T - 1][Y - 1] == 0)
		{
			pos.Set((float)((T - 1) * 1000), 0, (float)((Y - 1) * 1000));

			CQuaternion rot;
			rot.SetRotationDeg(CVector3::AxisY, 180);

			minimap[T - 1][Y - 1] = 43;

			MapPiece* mp = NewGO<MapPiece>(0);
			mp->init(pos, rot, Lkarb);
			PMS.push_back(mp);
			Maping(T - 1, Y - 1, 2, Lkarb);
			//mp->initPhysic();
		}

		x = 0;
		y = 0;
		for (x = 1; x < T - 1; x++)
		{

			if (minimap[x][0] == 0)
			{
				pos.Set((float)(x * 1000), 0, 0);

				CQuaternion rot;
				rot.SetRotationDeg(CVector3::AxisY, -90);

				minimap[x][0] = 40;

				MapPiece* mp = NewGO<MapPiece>(0);
				mp->init(pos, rot, right);
				PMS.push_back(mp);
				Maping(x, 0, 3, right);
				//mp->initPhysic();
			}
			if (minimap[x][Y - 1] == 0)
			{
				pos.Set((float)(x * 1000), 0, (float)((Y - 1) * 1000));

				CQuaternion rot;
				rot.SetRotationDeg(CVector3::AxisY, 90);

				minimap[x][Y - 1] = 43;

				MapPiece* mp = NewGO<MapPiece>(0);
				mp->init(pos, rot, right);
				PMS.push_back(mp);
				Maping(x, Y-1, 1, right);
				//mp->initPhysic();
			}

		}

		for (y = 1; y < Y - 1; y++)
		{
			if (minimap[0][y] == 0)
			{
				pos.Set(0, 0, (float)(y * 1000));

				minimap[0][y] = 40;

				MapPiece* mp = NewGO<MapPiece>(0);
				mp->init(pos, CQuaternion::Identity, right);
				PMS.push_back(mp);
				Maping(0, y, 0, right);
				//mp->initPhysic();
			}

			if (minimap[T - 1][y] == 0)
			{
				pos.Set((float)((T - 1) * 1000), 0, (float)(y * 1000));

				CQuaternion rot;
				rot.SetRotationDeg(CVector3::AxisY, 180);

				minimap[T - 1][y] = 43;

				MapPiece* mp = NewGO<MapPiece>(0);
				mp->init(pos, rot, right);
				PMS.push_back(mp);
				Maping(T-1, y, 2, right);
				//mp->initPhysic();
			}
		}
		MapPiece* mp;
		CQuaternion rot;
		int num;
		for (int xi = 1; xi < T - 1; xi++)
		{
			for (int yi = 1; yi < Y - 1; yi++)
			{
				if (minimap[xi][yi] == 0)
				{
					int r = round(Random().GetRandDouble());
					r = 0;
					switch (r)
					{
					case 0:
						num = (r + 1) * 10;

						pos.Set((float)(xi * 1000), 0, (float)(yi * 1000));

						r = Random().GetRandDouble() * 3;
						num += r;

						rot.SetRotationDeg(CVector3::AxisY, 90 * r);

						minimap[xi][yi] = num;

						mp = NewGO<MapPiece>(0);
						mp->init(pos, rot, right);
						PMS.push_back(mp);
						Maping(xi, yi, r, right);
						//mp->initPhysic();
						break;
					case 3:
						num = (r + 1) * 10;

						pos.Set((float)(xi * 1000), 0, (float)(yi * 1000));

						r = Random().GetRandDouble() * 3;
						num += r;

						rot.SetRotationDeg(CVector3::AxisY, 90 * r);

						map[xi][yi] = num;

						mp = NewGO<MapPiece>(0);
						mp->init(pos, rot, right);
						PMS.push_back(mp);
						//mp->initPhysic();
						break;
					case 2:
						num = (r + 1) * 10;

						pos.Set((float)(xi * 1000), 0, (float)(yi * 1000));

						r = Random().GetRandDouble() * 3;
						num += r;

						rot.SetRotationDeg(CVector3::AxisY, 90 * r);

						map[xi][yi] = num;

						mp = NewGO<MapPiece>(0);
						mp->init(pos, rot, right);
						PMS.push_back(mp);
						//mp->initPhysic();
						break;
					case 1:
						num = (r + 1) * 10;

						pos.Set((float)(xi * 1000), 0, (float)(yi * 1000));

						r = Random().GetRandDouble() * 3;
						num += r;

						rot.SetRotationDeg(CVector3::AxisY, 90 * r);

						map[xi][yi] = num;

						mp = NewGO<MapPiece>(0);
						mp->init(pos, rot, right);
						PMS.push_back(mp);
						//mp->initPhysic();
						break;
					}
				}
			}
		}
		delete(minimap);
		iniend = true;
		//5SetUP();
		sw.Stop();
		TK_LOG("Background thread time = %lf\n", sw.GetElapsed());
	});
#if 0
	tx = T;
	yy = Y;
	map = new int*[T];
	for (int i = 0; i < T; i++)
	{
		map[i] = new int[Y];
	}
	for (int y = 0; y < T; y++)
	{
		for (int x = 0; x < Y; x++)
		{
			map[y][x] = 0;
		}
	}
	CVector3 pos;
	int x, y, cnt = 0;

	x = Random().GetRandDouble() * (T-2) + 1;
	y = Random().GetRandDouble() * (Y-2) + 1;
	map[x][y] = 10;
	MapPiece* stm = NewGO<MapPiece>(0);
	{
		pos.Set((float)(x * 1000), 0, (float)(y * 1000));
		
		stm->init(pos,CQuaternion::Identity,(int)start);
		FindGO<Player>("player")->inipo = pos;
	}
	CQuaternion enro;
	int rm = (int)((T + Y) / 2);
	for (int root = 0; root < rm; root++)
	{
		CQuaternion rot;
		int c, ex = 0, r, count = 0;
		do
		{
			c = 0;
			r = Random().GetRandDouble() * 3;
			switch (r)
			{
			case 0:
				if (x - 1 != 0 && map[x - 1][y] == 0)
				{
					if (root == 0)
					{
						rot.SetRotationDeg(CVector3::AxisY, 180);
						stm->SetRot(rot);
						stm->initPhysic();
						cnt++;
					}
					else if (root == rm-1)
					{
						enro = CQuaternion::Identity;
					}
					x--;
					map[x][y] = 99;
					c++;
				}
				break;
			case 1:
				if (y + 1 != Y-1 && map[x][y + 1] == 0)
				{
					if (root == 0)
					{
						rot.SetRotationDeg(CVector3::AxisY, -90);
						stm->SetRot(rot);
						stm->initPhysic();
						cnt++;
					}
					else if (root == rm-1)
					{
						enro.SetRotationDeg(CVector3::AxisY, 90);
					}
					y++;
					map[x][y] = 99;
					c++;
				}
				break;
			case 2:
				if (x + 1 != T-1 && map[x + 1][y] == 0)
				{
					if (root == 0)
					{
						CQuaternion rot = CQuaternion::Identity;
						stm->SetRot(rot);
						stm->initPhysic();
						cnt++;
					}
					else if (root == rm-1)
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
						rot.SetRotationDeg(CVector3::AxisY, 90);
						stm->SetRot(rot);
						stm->initPhysic();
						cnt++;
					}
					else if (root == rm-1)
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
								rot.SetRotationDeg(CVector3::AxisY, 180);
								stm->SetRot(rot);
								stm->initPhysic();
								cnt++;
							}
							else if (root == rm-1)
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
								rot.SetRotationDeg(CVector3::AxisY, -90);
								stm->SetRot(rot);
								stm->initPhysic();
								cnt++;
							}
							else if (root == rm-1)
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
								CQuaternion rot = CQuaternion::Identity;
								stm->SetRot(rot);
								stm->initPhysic();
								cnt++;
							}
							else if (root == rm-1)
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
								rot.SetRotationDeg(CVector3::AxisY, 90);
								stm->SetRot(rot);
								stm->initPhysic();
								cnt++;
							}
							else if (root == rm-1)
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
			pos.Set((float)(x * 1000), 0, (float)(y * 1000));

			MapPiece* mp = NewGO<MapPiece>(0);
			mp->init(pos, CQuaternion::Identity, tile);
			mp->initPhysic();

			/*prefab::CSkinModelRender* sk = NewGO<prefab::CSkinModelRender>(0);
			sk->Init(L"modelData/pixie/pixie.cmo");
			sk->SetPosition(pos);*/
		}

	}
	map[x][y] = 20;
	{
		pos.Set((float)(x * 1000), 0, (float)(y * 1000));
		level.Init(L"level/end.tkl", [&](LevelObjectData &obj)
		{
			if (obj.EqualObjectName(L"end"))
			{
				MapPiece* em = NewGO<MapPiece>(0);
				em->init(pos, enro, end);
				em->initPhysic();
				return true;
			}
			else if (obj.EqualObjectName(L"Q"))
			{
				/*Q* q = NewGO<Q>(0, "Q");
				CVector3 qp = obj.position;
				qp += pos;
				q->pos = qp;*/
				return true;
			}
			return false;
		});
	}

	if (map[0][0] = 0)
	{
		pos.Set(0, 0, 0);
		
		map[0][0] = 30;

		MapPiece* mp = NewGO<MapPiece>(0);
		mp->init(pos, CQuaternion::Identity, Rkarb);
		mp->initPhysic();
	}
	if (map[0][Y-1] == 0)
	{
		pos.Set(0, 0, (float)((Y-1) * 1000));
		
		CQuaternion rot;
		rot.SetRotationDeg(CVector3::AxisY, 180);
		
		map[0][Y-1] = 33;

		MapPiece* mp = NewGO<MapPiece>(0);
		mp->init(pos, rot, Rkarb);
		mp->initPhysic();
	}

	if (map[T-1][0] == 0)
	{
		pos.Set((float)((T-1) * 1000), 0, 0);
		
		map[T-1][0] = 40;

		MapPiece* mp = NewGO<MapPiece>(0);
		mp->init(pos, CQuaternion::Identity, Lkarb);
		mp->initPhysic();
	}
	if (map[T-1][Y-1] == 0)
	{
		pos.Set((float)((T-1) * 1000), 0, (float)((Y-1) * 1000));
		
		CQuaternion rot;
		rot.SetRotationDeg(CVector3::AxisY, 180);
		
		map[T-1][Y-1] = 43;

		MapPiece* mp = NewGO<MapPiece>(0);
		mp->init(pos, rot, Lkarb);
		mp->initPhysic();
	}

	x = 0;
	y = 0;
	for (x = 1; x < T-1; x++)
	{

		if (map[x][0] == 0)
		{
			pos.Set((float)(x * 1000), 0, 0);
			
			CQuaternion rot;
			rot.SetRotationDeg(CVector3::AxisY, -90);
			
			map[x][0] = 40;

			MapPiece* mp = NewGO<MapPiece>(0);
			mp->init(pos, rot, right);
			mp->initPhysic();
		}
		if (map[x][Y-1] == 0)
		{
			pos.Set((float)(x * 1000), 0, (float)((Y-1) * 1000));
			
			CQuaternion rot;
			rot.SetRotationDeg(CVector3::AxisY, 90);
			
			map[x][Y-1] = 43;

			MapPiece* mp = NewGO<MapPiece>(0);
			mp->init(pos, rot, right);
			mp->initPhysic();
		}

	}

	for (y = 1; y < Y-1; y++)
	{
		if (map[0][y] == 0)
		{
			pos.Set(0, 0, (float)(y * 1000));
			
			map[0][y] = 40;

			MapPiece* mp = NewGO<MapPiece>(0);
			mp->init(pos, CQuaternion::Identity, right);
			mp->initPhysic();
		}

		if (map[T-1][y] == 0)
		{
			pos.Set((float)((T-1) * 1000), 0, (float)(y * 1000));
			
			CQuaternion rot;
			rot.SetRotationDeg(CVector3::AxisY, 180);
			
			map[T-1][y] = 43;

			MapPiece* mp = NewGO<MapPiece>(0);
			mp->init(pos, rot, right);
			mp->initPhysic();
		}
	}
	MapPiece* mp;
	CQuaternion rot;
	int num;
	for (int xi = 1; xi < T-1; xi++)
	{
		for (int yi = 1; yi < Y-1; yi++)
		{
			if (map[xi][yi] == 0)
			{
				int r = round(Random().GetRandDouble());
				r = 0;
				switch (r)
				{
				case 0:
					num = (r + 1) * 10;

					pos.Set((float)(xi * 1000), 0, (float)(yi * 1000));
					
					r = Random().GetRandDouble() * 3;
					num += r;
					
					rot.SetRotationDeg(CVector3::AxisY, 90 * r);

					map[xi][yi] = num;

					mp = NewGO<MapPiece>(0);
					mp->init(pos, rot, right);
					mp->initPhysic();
					break;
				case 3:
					num = (r + 1) * 10;

					pos.Set((float)(xi * 1000), 0, (float)(yi * 1000));
					
					r = Random().GetRandDouble() * 3;
					num += r;
					
					rot.SetRotationDeg(CVector3::AxisY, 90 * r);

					map[xi][yi] = num;

					mp = NewGO<MapPiece>(0);
					mp->init(pos, rot, right);
					mp->initPhysic();
					break;
				case 2:
					num = (r + 1) * 10;

					pos.Set((float)(xi * 1000), 0, (float)(yi * 1000));
					
					r = Random().GetRandDouble() * 3;
					num += r;
					
					rot.SetRotationDeg(CVector3::AxisY, 90 * r);

					map[xi][yi] = num;

					mp = NewGO<MapPiece>(0);
					mp->init(pos, rot, right);
					mp->initPhysic();
					break;
				case 1:
					num = (r + 1) * 10;

					pos.Set((float)(xi * 1000), 0, (float)(yi * 1000));
					
					r = Random().GetRandDouble() * 3;
					num += r;

					rot.SetRotationDeg(CVector3::AxisY, 90 * r);

					map[xi][yi] = num;

					mp = NewGO<MapPiece>(0);
					mp->init(pos, rot, right);
					mp->initPhysic();
					break;
				}
			}
		}
	}
#endif
}

void BackGround::Maping(int x, int y,int r,int m)
{
	int nx = x * 3 + 2;
	int ny = y * 3 + 2;
	int tip[3][3];
	for (int cx = 0; cx < 3; cx++)
	{
		for (int cy = 0; cy < 3; cy++)
			tip[cx][cy] = 0;
	}
	switch (m)
	{
	case start:
		tip[0][0] = 1;
		tip[0][2] = 1;
		tip[2][0] = 1;
		tip[2][1] = 1;
		tip[2][2] = 1;
		break;
	case end:
		tip[2][0] = 1;
		tip[2][2] = 1;
		tip[0][0] = 1;
		tip[0][1] = 1;
		tip[0][2] = 1;
		break;
	case tile:
		break;
	case right:
		tip[0][2] = 1;
		tip[1][2] = 1;
		tip[2][2] = 1;
		break;
	case Lkarb:
		tip[0][0] = 1;
		tip[0][1] = 1;
		tip[0][2] = 1;
		tip[1][0] = 1;
		tip[2][0] = 1;
		break;
	case Rkarb:
		tip[0][0] = 1;
		tip[0][1] = 1;
		tip[0][2] = 1;
		tip[1][2] = 1;
		tip[2][2] = 1;
		break;
	}
	int res[3][3] = { 0 };
	for (int i = 0; i < r + 1; i++)
	{
		res[0][2] = tip[0][0];
		res[1][2] = tip[0][1];
		res[2][2] = tip[0][2];
		res[0][1] = tip[1][0];
		res[1][1] = tip[1][1];
		res[2][1] = tip[1][2];
		res[0][0] = tip[2][0];
		res[1][0] = tip[2][1];
		res[2][0] = tip[2][2];
		for (int px = 0; px < 3; px++)
		{
			for (int py = 0; py < 3; py++)
			{
				tip[px][py] = res[px][py];
			}
		}
	}
	map[nx-2][ny-2] = tip[0][0];
	map[nx - 2][ny - 1] = tip[0][1];
	map[nx - 2][ny] = tip[0][2];
	map[nx - 1][ny - 2] = tip[1][0];
	map[nx - 1][ny - 1] = tip[1][1];
	map[nx - 1][ny] = tip[1][2];
	map[nx][ny - 2] = tip[2][0];
	map[nx][ny - 1] = tip[2][1];
	map[nx][ny] = tip[2][2];
	/*switch (r)
	{
	case 0:
		break;
	case 1:
		res[0][2] = tip[0][0];
		res[1][2] = tip[0][1];
		res[2][2] = tip[0][2];
		res[0][1] = tip[1][0];
		res[1][1] = tip[1][1];
		res[2][1] = tip[1][2];
		res[0][0] = tip[2][0];
		res[1][0] = tip[2][1];
		res[2][0] = tip[2][2];
		break;
	case 2:
		res[2][2] = tip[0][0];
		res[2][1] = tip[0][1];
		res[2][0] = tip[0][2];
		res[1][2] = tip[1][0];
		res[1][1] = tip[1][1];
		res[1][0] = tip[1][2];
		res[0][2] = tip[2][0];
		res[0][1] = tip[2][1];
		res[0][0] = tip[2][2];
		break;
	case 3:
		res[2][2] = tip[0][0];
		res[2][1] = tip[0][1];
		res[2][0] = tip[0][2];
		res[1][2] = tip[1][0];
		res[1][1] = tip[1][1];
		res[1][0] = tip[1][2];
		res[0][2] = tip[2][0];
		res[0][1] = tip[2][1];
		res[0][0] = tip[2][2];
		break;
	}*/
}

void BackGround::SetUP()
{
	CStopwatch sw;
	sw.Start();
	for (auto mp : PMS)
	{
		mp->Create();
	}
	sw.Stop();
	TK_LOG("BackGround::Setup time = %lf\n", sw.GetElapsed());
}

void BackGround::PostRender(CRenderContext & rc)
{
	if (false&&iniend)
	{
		font.Begin(rc);
		//wchar_t text[255];
		float px = -300;
		float py = -300;
		for (int x = 0; x < tx; x++)
		{
			for (int y = 0; y < yy; y++)
			{
				wchar_t n[256];
				int num = map[x][y];
				swprintf_s(n, L"%01d",num);
				font.Draw(n, { px + y * 10,py + x * 10 }, CVector4::White, 0, 0.2f);
			}
		}
		font.End(rc);
	}
}
