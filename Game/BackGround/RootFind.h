#pragma once

struct Node
{
	Node* linkNode[8];
	Node* parentNode;
	float movecost = 0;
	int mapID = 0;
	bool isFind = false;
};
class RootFind
{
public:
	void CreateNode(int T,int Y,int** map);
	CVector3 FindRoot(float sy, float sx, float ty, float tx);
	Node** nodeMap;
	int mt;
	int my;
};