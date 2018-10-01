#include "stdafx.h"
#include "RootFind.h"

bool RootFind::Start()
{
	return true;
}
void RootFind::CreateNodeMap(int T,int Y,int** map)
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

CVector3 RootFind::FindRoot(CVector3 start,CVector3 target)
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

	int spz = round((start.z) / 1000.0f / BASE);
	int spx = round((start.x) / 1000.0f / BASE);
	Node* startNode = &nodeMap[spz][spx];
	startNode->movecost = 0;
	while (true)
	{
		Node* prosNode = NULL;
		for (int y = 0; y < mt; y++)
		{
			for (int x = 0; x < my; x++)
			{
				Node* node = &nodeMap[y][x];
				if (node->isFind || node->movecost < 0)
					continue;
				if (!prosNode)
				{
					prosNode = node;
					continue;
				}
				if (node->movecost < prosNode->movecost)
					prosNode = node;
			}
		}
		if (!prosNode)
			break;
		prosNode->isFind = true;
		for (int i = 0; i < 8; i++)
		{
			Node* node = prosNode->linkNode[i];
			if (node == NULL)
				continue;
			CVector3 dif;
			if(prosNode->parentNode != NULL)
				dif = prosNode->parentNode->pos*(BASE * 1000.0f) - prosNode->pos*(BASE * 1000.0f);
			else
				dif = startNode->pos*(BASE * 1000.0f) - prosNode->pos*(BASE * 1000.0f);
			float cost = dif.Length();
			bool isUpdata = (node->movecost < 0 || node->movecost > cost);
			if (isUpdata)
			{
				node->movecost = cost;
				node->parentNode = prosNode;
			}
		}
	}
	int tpz = round(target.z / 1000.0f / BASE);
	int tpx = round(target.x / 1000.0f / BASE);
	Node* node = &nodeMap[tpz][tpx];
	while (node->parentNode == startNode)
	{
		node = node->parentNode;
	}
	CVector3 dif = node->pos*(BASE * 1000.0f) - startNode->pos*(BASE * 1000.0f);
	CVector3 root = {dif.x,0,dif.y};
	root.Normalize();
	return root;
}

void RootFind::BuildNode()
{
	for (int y = 0; y < mt; y++)
	{
		for (int x = 0; x < my; x++)
		{
			Node* node = &nodeMap[y][x];
			for (int l = 0; l < 8; l++)
				node->linkNode[l] = NULL;

			if (y - 1 >= 0 && x - 1 >= 0)
				node->linkNode[0] = &nodeMap[y - 1][x - 1];
			if (y - 1 >= 0 && x >= 0)
				node->linkNode[1] = &nodeMap[y - 1][x];
			if (y - 1 >= 0 && x + 1 >= 0)
				node->linkNode[2] = &nodeMap[y - 1][x + 1];

			if (y >= 0 && x - 1 >= 0)
				node->linkNode[3] = &nodeMap[y][x - 1];
			if (y >= 0 && x + 1 >= 0)
				node->linkNode[4] = &nodeMap[y][x + 1];

			if (y + 1 >= 0 && x - 1 >= 0)
				node->linkNode[5] = &nodeMap[y + 1][x - 1];
			if (y + 1 >= 0 && x >= 0)
				node->linkNode[6] = &nodeMap[y + 1][x];
			if (y + 1 >= 0 && x + 1 >= 0)
				node->linkNode[7] = &nodeMap[y+1][x+1];
			node->pos.x = x;
			node->pos.y = y;
		}
	}
}
