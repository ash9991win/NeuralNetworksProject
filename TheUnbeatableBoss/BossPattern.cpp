#include"pch.h"
#include "BossPattern.h"


void PatternFollower::Update(float deltaTime)
{
	if (mCurrentAction->GetState() == ActionState::STARTED)
	{
		mCurrentAction->ChangeState(ActionState::RUNNING);
	}
	if (mCurrentAction->GetState() == ActionState::RUNNING)
	{
		mCurrentAction->Update(deltaTime);
	}
	else if (mCurrentAction->GetState() == ActionState::EXITING)
	{
		mCurrentActionIndex++;
		if (mCurrentActionIndex >= mListOfActions.size())
			OnPatternCompletion.Invoke();
		else
			mCurrentAction = mListOfActions[mCurrentActionIndex];
	}
}

void PatternFollower::BeginPlay()
{
	for (auto action : mListOfActions)
	{
		action->SetOwner(Owner);
		action->SetTarget(Target);
		action->ChangeState(ActionState::STARTED);
	}
	mCurrentActionIndex = 0;
	mCurrentAction = mListOfActions[0];
	mCurrentAction->ChangeState(ActionState::STARTED);
}

PatternFollower::PatternFollower(Actor* owner,Actor* target)
	:Owner(owner),Target(target)
{
}


PatternFollower::~PatternFollower()
{
}
