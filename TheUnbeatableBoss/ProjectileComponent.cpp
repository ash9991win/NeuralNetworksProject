#include"pch.h"
#include "ProjectileComponent.h"
#include"Actor.h"


ProjectileComponent::ProjectileComponent()
{
}


ProjectileComponent::~ProjectileComponent()
{
}

void ProjectileComponent::Update(float deltaTime)
{
	static float maxTime = (mInitialVelocity.y / GRAVITY);
	static float totalTimeTaken = 2 * maxTime;
	if (totalTimeTaken > 0)
	{
		sf::Vector2f acceleration;
		acceleration.x = 0;
		acceleration.y = GRAVITY;
		mVelocity.x = mInitialVelocity.x;
		if (totalTimeTaken > (maxTime / 2))
		{
			mVelocity.y = mInitialVelocity.y - GRAVITY * deltaTime;
		}
		else
		{
			mVelocity.y = GRAVITY * deltaTime - mInitialVelocity.y;
		}

		totalTimeTaken -= deltaTime;
		mOwner->mPosition += deltaTime * mVelocity;
	}
}

void ProjectileComponent::SetLaunchAngle(float angle)
{
	mLaunchAngle = angle;
	mInitialVelocity.x = 1000 * cos(angle * 0.0174533f);
	mInitialVelocity.y = 1000 * sin(angle * 0.0174533f);
}

void ProjectileComponent::BeginPlay()
{
}
