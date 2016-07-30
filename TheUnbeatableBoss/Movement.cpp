#include"pch.h"
#include "Movement.h"
#include"Bullet.h"
#include"World.h"
#include"Boss.h"
#include"Player.h"
#include"ShieldActor.h"
#include"GlowEffects.h"
RTTI_DEFINITION(Shoot);
RTTI_DEFINITION(Shield)
RTTI_DEFINITION(MoveUp);
RTTI_DEFINITION(MoveDown);
RTTI_DEFINITION(MoveLeft);
RTTI_DEFINITION(MoveRight);

void Shoot::Update(float deltaTime)
{
	static float CurrentTime = 0.0f;
	static float FireRate = 0.0f;
	CurrentTime += deltaTime;
	if (CurrentTime <= mDuration)
	{
		FireRate += deltaTime;
		if (FireRate >= mFireRate)
		{
		auto bullet = World::SpawnActor<Bullet>("Bullet",mOwner,mTarget,*mBulletSprite,20,20,2000);
			FireRate = 0;
		}
		
	}
	else
	{
		CurrentTime = 0;
		ChangeState(ActionState::EXITING);
	}
}

void Shoot::BeginPlay()
{
}

void Shield::Update(float deltaTime)
{
	static float CurrentTime = 0;
	//Change the color of the boss
	
	if (CurrentTime <= mDuration)
	{
		mOwner->Shield();
		CurrentTime += deltaTime;
	}
	else
	{
		mOwner->UnShield();
		mShieldActor = nullptr;
		CurrentTime = 0;
		ChangeState(ActionState::EXITING);
	}
}

void Shield::BeginPlay()
{
}

void MoveUp::Update(float deltaTime)
{
	static float CurrentTime = 0;
	if (CurrentTime <= mDuration)
	{
		//Keep moving up
		if (mOwner)
		{
			mOwner->mPosition.y -= mOwner->speed * deltaTime;
			auto& playerPosition = mOwner->mPosition;
			if (playerPosition.y <= 0)
			{
				playerPosition.y += mOwner->speed * deltaTime;
			}
		}
		CurrentTime += deltaTime;
	}
	else
	{
		CurrentTime = 0;
		ChangeState(ActionState::EXITING);
	}
}

void MoveUp::BeginPlay()
{
}

void MoveLeft::Update(float deltaTime)
{
	static float CurrentTime = 0;
	if (CurrentTime <= mDuration)
	{
		//Keep moving up
		if (mOwner)
		{
			mOwner->mPosition.x -= mOwner->speed * deltaTime;
			auto& playerPosition = mOwner->mPosition;
			if (playerPosition.x <= 0)
			{
				playerPosition.x += mOwner->speed * deltaTime;
			}
		}
		CurrentTime += deltaTime;
	}
	else
	{
		CurrentTime = 0;
		ChangeState(ActionState::EXITING);
	}
}

void MoveLeft::BeginPlay()
{
}

void MoveRight::Update(float deltaTime)
{
	static float CurrentTime = 0;
	if (CurrentTime <= mDuration)
	{
		//Keep moving up
		if (mOwner)
		{
			mOwner->mPosition.x += mOwner->speed * deltaTime;
			auto& playerPosition = mOwner->mPosition;
			if (playerPosition.x + mOwner->mSpriteWidth >= WINDOW_WIDTH)
			{
				playerPosition.x -= mOwner->speed * deltaTime;
			}
		}
		CurrentTime += deltaTime;
	}
	else
	{
		CurrentTime = 0;
		ChangeState(ActionState::EXITING);
	}
}

void MoveRight::BeginPlay()
{
}

void MoveDown::Update(float deltaTime)
{
	static float CurrentTime = 0;
	if (CurrentTime <= mDuration)
	{
		//Keep moving up
		if (mOwner)
		{
			mOwner->mPosition.y += mOwner->speed * deltaTime;
			auto& playerPosition = mOwner->mPosition;
			if (playerPosition.y + mOwner->mSpriteHeight >= WINDOW_HEIGHT)
			{
				playerPosition.y -= mOwner->speed * deltaTime;
			}
		}
		
		CurrentTime += deltaTime;
	}
	else
	{
		CurrentTime = 0;
		ChangeState(ActionState::EXITING);
	}
}

void MoveDown::BeginPlay()
{
}
