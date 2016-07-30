#pragma once
#include"ActionComponent.h"
class ActionFactory
{
	static map<std::uint64_t, shared_ptr<Action>> ActionTable;
	static vector<shared_ptr<Action>> ActionList;
	friend class PatternChooser;
public:
	static shared_ptr<Action> GetARandomAction();
	static shared_ptr<Action> GetActionOfType(std::uint64_t id);
	static shared_ptr<Action> GetActionOfType(string name);
	static void InitializeFactory();
	ActionFactory() = default;
	~ActionFactory() = default;
};

