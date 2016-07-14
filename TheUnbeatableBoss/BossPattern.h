#pragma once
#include"ActionComponent.h"
class BossPattern
{
private:
	vector<shared_ptr<Action>> mListOfActions;
	int mCurrentActionIndex;
	shared_ptr<Action> mCurrentAction;
	Actor* Owner;
public:
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
	}
	void ResetCurrentAction() {
		mCurrentActionIndex = 0;
		mCurrentAction = mListOfActions[mCurrentActionIndex];
	}
	void Update(float deltaTime);
	void BeginPlay();
	BossPattern(Actor* owner);
	~BossPattern();
};

