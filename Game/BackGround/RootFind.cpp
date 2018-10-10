#include "stdafx.h"
#include <iostream>
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

CVector3 RootFind::FindRoot(CVector3 start,CVector3 target,Piece &piece)
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

	int spz = ((start.z) / 1000.0f / BASE)+1;
	int spx = ((start.x) / 1000.0f / BASE)+1;

	if (spz != piece.pos.y || spx != piece.pos.x)
	{
		piece.old = piece.pos;
	}
	if (nodeMap[spz][spx].mapID == 1)
	{
		spz = piece.old.y;
		spx = piece.old.x;
	}
	piece.pos.y = spz;
	piece.pos.x = spx;
	
	Node* startNode = &nodeMap[spx][spz];
	startNode->movecost = 0;

	/*prefab::CSkinModelRender* sk = NewGO < prefab::CSkinModelRender>(0);
	sk->Init(L"modelData/mamono/mamono.cmo");
	sk->SetScale({ 2.0f,0.1f,0.1f });
	CVector3 nonp = { startNode->pos.x,0,startNode->pos.y };
	CVector3 t3 = { 333.333f,500.0f,333.333f };
	CVector3 spo = nonp * (BASE * 1000.0f);
	sk->SetPosition(spo);
*/
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
			if(prosNode->parentNode != NULL || true)
				dif = node->pos*(BASE * 1000.0f) - prosNode->pos*(BASE * 1000.0f);
			else
				dif = startNode->pos*(BASE * 1000.0f) - prosNode->pos*(BASE * 1000.0f);
			float cost = dif.Length();
			if (i == 0 || i == 2 || i == 5 || i == 7)
			{
				//cost *= sqrtf(2);
			}
			bool isUpdata = ((node->movecost < 0) || (node->movecost > cost)) && (node != prosNode->parentNode);
			if (isUpdata)
			{
				node->movecost = cost;
				node->parentNode = prosNode;
			}
		}
	}
	int tpz = (target.z / 1000.0f / BASE);
	int tpx = (target.x / 1000.0f / BASE);
	Node* node = &nodeMap[tpz][tpx];
	int count = 0;/*
	for(prefab::CSkinModelRender* s : msa)
	{
		DeleteGO(s);
	}
	msa.clear();*/
	while (node->parentNode != startNode)
	{
		CVector2 np = { node->parentNode->pos.x,node->parentNode->pos.y };
		piece.root.push_back(np);
		node = node->parentNode;

		prefab::CSkinModelRender* sk = NewGO < prefab::CSkinModelRender>(0);
		sk->Init(L"modelData/mamono/mamono.cmo");
		sk->SetScale({ 2.0f,0.1f,0.1f });
		CVector3 nop = { node->pos.x,0,node->pos.y };
		CVector3 three = { 333.333f,500.0f,333.333f };
		CVector3 spo = nop * (BASE * 1000.0f);
		sk->SetPosition(spo);
		msa.push_back(sk);

		std::cout << count << "x:" << np.x << "y:" << np.y << "\n";
		count++;
		if (count >= 300)
			break;
	}
	//CVector3 dif = node->pos*(BASE * 1000.0f) - startNode->pos*(BASE * 1000.0f);
	CVector3 nop = { node->pos.x,0,node->pos.y };
	CVector3 three = { 333.333f,0.0f,333.333f };

	CVector3 dif = nop*(BASE * 1000.0f) - startNode->pos;
	//CVector3 dif = nop*(BASE * 1000.0f) - start;

	CVector3 root = {dif.x,0,dif.z};
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
			if (y - 1 >= 0)
				node->linkNode[1] = &nodeMap[y - 1][x];
			if (y - 1 >= 0 && x + 1 < mt)
				node->linkNode[2] = &nodeMap[y - 1][x + 1];

			if (x - 1 >= 0)
				node->linkNode[3] = &nodeMap[y][x - 1];
			if (x + 1 < mt)
				node->linkNode[4] = &nodeMap[y][x + 1];

			if (y + 1 < my && x - 1 >= 0)
				node->linkNode[5] = &nodeMap[y + 1][x - 1];
			if (y + 1 < my)
				node->linkNode[6] = &nodeMap[y + 1][x];
			if (y + 1 < my && x + 1 < mt)
				node->linkNode[7] = &nodeMap[y+1][x+1];
			node->pos.x = x;
			node->pos.y = y;
		}
	}
}
