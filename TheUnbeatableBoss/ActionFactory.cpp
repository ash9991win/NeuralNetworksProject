#include"pch.h"
#include "ActionFactory.h"
#include"Movement.h"
#include<assert.h>
#define CREATE_ACTION(ActionType) \
auto ActionType##Variable = make_shared<ActionType>(#ActionType); \
ActionTable[ActionType::TypeIdClass()] = ActionType##Variable; \
ActionList.push_back(ActionType##Variable); 

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

shared_ptr<Action> ActionFactory::GetActionOfType(string name)
{
	shared_ptr<Action> result;
	for_each(ActionList.begin(), ActionList.end(), [&result, name](const shared_ptr<Action>& action) { if (action->Name() == name) { result = action; } });
	return result;
}

void ActionFactory::InitializeFactory()
{
	//auto shootAction = make_shared<Shoot>("Shoot");
	//auto shieldAction = make_shared<Shield>("Shield");
	//auto moveUp = make_shared<MoveUp>("Move Up");
	////All the other actions here

	////ActionTable[Shoot::TypeIdClass()] = shootAction;
	////ActionTable[Shield::TypeIdClass()] = shieldAction;
	//ActionTable[MoveUp::TypeIdClass()] = moveUp;
	////ActionList.push_back(shieldAction);
	////ActionList.push_back(shootAction);
	//ActionList.push_back(moveUp);
	CREATE_ACTION(MoveUp)
	CREATE_ACTION(MoveLeft);
	CREATE_ACTION(MoveRight);
	CREATE_ACTION(MoveDown);
	CREATE_ACTION(Shoot);
	CREATE_ACTION(Shield);
}

