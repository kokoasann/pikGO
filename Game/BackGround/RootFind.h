#pragma once

struct Node
{

	Node* linkNode[8];
	Node* parentNode = NULL;
	CVector3 pos;
	float movecost = -1.0f;
	int mapID = 0;
	bool isFind = false;
};
struct Piece
{
	CVector2 pos;
	CVector2 old;
	std::vector<CVector2> root;
};
class RootFind:public IGameObject
{
public:
	bool Start();
	void CreateNodeMap(int T,int Y,int** map);
	CVector3 FindRoot(CVector3 start, CVector3 target,Piece &piece);
	void BuildNode();

	Node** GetNodeMap()
	{
		return nodeMap;
	}
private:
	const float BASE = 1.0f / 3.0f;
	Node** nodeMap;
	int mt;
	int my;

	std::list<prefab::CSkinModelRender*> msa;
};