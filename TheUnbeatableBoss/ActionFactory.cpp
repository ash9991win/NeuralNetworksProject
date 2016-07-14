#include"pch.h"
#include "ActionFactory.h"
#include"Movement.h"
#include<assert.h>
map<std::uint64_t,shared_ptr<Action>> ActionFactory::ActionTable;
vector<shared_ptr<Action>> ActionFactory::ActionList;
shared_ptr<Action> ActionFactory::GetARandomAction()
{
	int index = RandInt(0, ActionList.size() - 1);
	return ActionList[index];
}

shared_ptr<Action> ActionFactory::GetActionOfType(std::uint64_t id)
{
	assert(ActionTable.find(id) != ActionTable.end());
	return ActionTable[id];
}

void ActionFactory::InitializeFactory()
{
	auto movementAction = make_shared<Movement>("Movement");
	auto shootAction = make_shared<Shoot>("Shoot");
	auto shieldAction = make_shared<Shield>("Shield");

	//All the other actions here

	ActionTable[Movement::TypeIdClass()] = movementAction;
	ActionTable[Shoot::TypeIdClass()] = shootAction;
	ActionTable[Shield::TypeIdClass()] = shieldAction;

	ActionList.push_back(movementAction);
	ActionList.push_back(shieldAction);
	ActionList.push_back(shootAction);
}

