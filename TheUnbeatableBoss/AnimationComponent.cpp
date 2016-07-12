#include"pch.h"
#include"ResourceManager.h"
#include"World.h"
#include"Actor.h"
#include "AnimationComponent.h"
AnimationComponent::AnimationComponent(bool autoP)
	:autoPlay(autoP)
{
}

void AnimationComponent::SetFrames(std::vector<std::string> spriteNames)
{
	for (auto& name : spriteNames)
	{
		auto sprite = ResourceManager::LoadSprite(name);
		mFrames.push_back(*sprite);
	}
	mMaxFrame = spriteNames.size() - 1;
	mTimeBetweenFrames = 1.0f;
}

void AnimationComponent::SetTimeBetweenFrames(float value)
{
	mTimeBetweenFrames = value;
}

void AnimationComponent::SetFrameDimensions(float width, float height)
{
	mFrameWidth = width;
	mFrameHeight = height;
	for (auto& frames : mFrames)
	{
		frames.setScale(mFrameWidth / frames.getLocalBounds().width, mFrameHeight / frames.getLocalBounds().height);
	}
}

AnimationComponent::~AnimationComponent()
{
}

void AnimationComponent::Update(float deltaTime)
{
	if (autoPlay)
	{
		if (mCurrentTime >= mTimeBetweenFrames)
		{
			mCurrentFrame++;
			if (mCurrentFrame > mMaxFrame)
			{
				mCurrentFrame = 0;
			}
			mCurrentTime = 0;
		}
		mCurrentTime += deltaTime;

	}
	mOwner->mSprite = mFrames[mCurrentFrame];
}

void AnimationComponent::PlayNext()
{
	mCurrentFrame++;
	if (mCurrentFrame > mMaxFrame)
	{
		mCurrentFrame = 0;
	}
}

void AnimationComponent::PlayPrev()
{
	mCurrentFrame--;
	if (mCurrentFrame < mMaxFrame)
	{
		mCurrentFrame = 0;
	}
}

void AnimationComponent::Stop()
{
	mCurrentFrame = 0;
}

void AnimationComponent::BeginPlay()
{
	mCurrentFrame = 0;
	mCurrentTime = 0;
}
