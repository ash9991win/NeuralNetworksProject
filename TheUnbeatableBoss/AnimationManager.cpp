#include"pch.h"
#include "AnimationManager.h"
#include"ResourceManager.h"
#include"Actor.h"
void AnimationManager::AddAnimation(AnimationID id,int startFrame, int lastFrame, Actor * owner, float timeBetween)
{
	Animation newAnim;
	newAnim.startFrame = startFrame;
	newAnim.endFrame = lastFrame;
	newAnim.owner = owner;
	newAnim.timeBetween = timeBetween;
	newAnim.currentFrame = startFrame;
	newAnim.currentIndex = 0;
	for (int i = startFrame; i <= lastFrame; i++)
	{
		newAnim.Frames.push_back(*ResourceManager::LoadAnimationFrame(i));
	}
	for (auto& frame : newAnim.Frames)
	{

			frame.setScale(owner->mSpriteWidth / frame.getLocalBounds().width, owner->mSpriteHeight / frame.getLocalBounds().height);
	}
	
	mAnimationTable[id] = newAnim;
}

void AnimationManager::AddAnimation(AnimationID id)
{
	switch (id)
	{
	case AnimationID::PlayerIdleAnimation: {
		AddAnimation(id, 5, 9, mOwner);
		break; }
	case AnimationID::PlayerRightWalkAnimation: {
		AddAnimation(id, 10, 14, mOwner);
		break;
	}
	case AnimationID::PlayerLeftWalkAnimation: {
		AddAnimation(id, 16, 19, mOwner);
		break;
	}
	case AnimationID::BossIdleAnimation:{
		AddAnimation(id, 0, 4, mOwner);
		break;
    }
	}
}



void AnimationManager::PlayAnimation(AnimationID id)
{
	if (mAnimationTable.find(id) == mAnimationTable.end())
		AddAnimation(id);
	mCurrentAnimation = &mAnimationTable[id];
}

void AnimationManager::Update(float deltaTime)
{
	static float CurrentTime = 0;
	if (CurrentTime >= mCurrentAnimation->timeBetween)
	{
		mCurrentAnimation->currentFrame++;
		mCurrentAnimation->currentIndex++;
		if (mCurrentAnimation->currentFrame > mCurrentAnimation->endFrame)
		{
			mCurrentAnimation->currentFrame = mCurrentAnimation->startFrame;
			mCurrentAnimation->currentIndex = 0;
		}
		CurrentTime = 0.0f;
	}
	CurrentTime += deltaTime;
	mCurrentAnimation->owner->mSprite = mCurrentAnimation->Frames[mCurrentAnimation->currentIndex];
}

void AnimationManager::BeginPlay()
{
	Enable = true;
}
