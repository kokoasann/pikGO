#pragma once

class Creature;
class CreatureManager:public IGameObject
{
public:
	bool Start() override;
	void add(Creature* C);
	void deleteC(Creature* C);
	void Creatures(std::function<void(Creature* crea)> fnc);

private:
	std::list<Creature*> creatureList;
};