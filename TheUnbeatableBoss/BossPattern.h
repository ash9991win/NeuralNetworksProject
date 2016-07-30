#pragma once
#include"ActionComponent.h"
class PatternFollower
{
private:
	vector<shared_ptr<Action>> mListOfActions;
	int mCurrentActionIndex;
	shared_ptr<Action> mCurrentAction;
	Actor* Owner;
	Actor* Target;
public:
	delegate<void> OnPatternCompletion;
	void EnequeAction(shared_ptr<Action> action)
	{
		if (mListOfActions.size() < CHROMO_LENGTH)
		{
			mListOfActions.push_back(action);
		}
	}
	
	shared_ptr<Action> GetCurrentAction()
	{
		return mCurrentAction;
	}
	void AssignActions( vector<shared_ptr<Action>> actions)
	{
		mListOfActions = actions;
		for (auto action : mListOfActions)
		{
			action->SetOwner(Owner);
			action->SetTarget(Target);
			action->ChangeState(ActionState::STARTED);
		}
	}
	void ResetCurrentAction() {
		mCurrentActionIndex = 0;
		for (auto& action : mListOfActions)
		{
			action->ChangeState(ActionState::STARTED);
		}
		mCurrentAction = mListOfActions[mCurrentActionIndex];
	}
	void Update(float deltaTime);
	void BeginPlay();
	PatternFollower(Actor* owner,Actor* target);
	~PatternFollower();
};

