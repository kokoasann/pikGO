#pragma once
#include "tkEngine/physics/tkPhysicsStaticObject.h"

class MapPiece;
class BackGround :public IGameObject
{
public:
	enum maps
	{
		start,
		end,
		tile,
		right,
		Lkarb,
		Rkarb
	};
	~BackGround();
	bool Start() override;
	void init(int T ,int Y);
	void Maping(int x, int y,int r,int m);
	void SetUP();
	void PostRender(CRenderContext& rc);

	void TestMaping();

	int** GetMap()
	{
		return map;
	}

	bool GetInitEnd()
	{
		return iniend;
	}

	CVector3 GetQpos()
	{
		return Qpos;
	}

private:
	CFont font;

	int tx = 0, yy = 0;
	int **map;
	bool iniend = false;
	//prefab::CSkinModelRender* start = nullptr;
	//prefab::CSkinModelRender* end = nullptr;
	std::list<prefab::CSkinModelRender*> maps;
	CVector3 startpos = CVector3::Zero,endpos = CVector3::Zero;

	std::list<MapPiece*> PMS;
	//std::vector<CPhysicsStaticObject> psolist;
	//CPhysicsStaticObject psoa[900];
	//CPhysicsStaticObject pso,pso2;

	CLevel level;
	CVector3 Qpos;
	
	std::thread* initThread = nullptr;
	std::list<MapPiece*> maplist;
};