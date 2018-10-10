#pragma once

class PixieSpawner:public IGameObject
{
public:
	bool Start();
	void init(int T, int Y, int RC, int RM);
	void TestSpawn();
};