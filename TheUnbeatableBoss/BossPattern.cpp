#include"pch.h"
#include "BossPattern.h"


void BossPattern::Update(float deltaTime)
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
			ResetCurrentAction();
		else
			mCurrentAction = mListOfActions[mCurrentActionIndex];
	}
}

void BossPattern::BeginPlay()
{
	for (auto action : mListOfActions)
	{
		action->SetOwner(Owner);
	}
	mCurrentActionIndex = 0;
	mCurrentAction = mListOfActions[0];
	mCurrentAction->ChangeState(ActionState::STARTED);
}

BossPattern::BossPattern(Actor* owner)
	:Owner(owner)
{
}


BossPattern::~BossPattern()
{
}
