#include "stdafx.h"
#include "RootFind.h"

void RootFind::CreateNode(int T,int Y,int** map)
{
	mt = T*3, my = Y*3;
	nodeMap = new Node*[mt];
	for (int i = 0; i < mt; i++)
	{
		nodeMap[i] = new Node[my];
	}
	for (int y = 0; y < mt; y++)
	{
		for (int x = 0; x < my; x++)
		{
			nodeMap[y][x].mapID = map[y][x];
			nodeMap[y][x].parentNode = NULL;

		}
	}
}

CVector3 RootFind::FindRoot(float sy, float sx,float ty,float tx)
{
	for (int iy = 0; iy < mt; iy++)
	{
		for (int ix = 0; ix < my; ix++)
		{
			nodeMap[iy][ix].movecost = -1.0f;
			nodeMap[iy][ix].isFind = false;
			if (nodeMap[iy][ix].mapID == 1)
			{
				nodeMap[iy][ix].isFind = true;
			}
			nodeMap[iy][ix].parentNode = NULL;
		}
	}

	return CVector3();
}
