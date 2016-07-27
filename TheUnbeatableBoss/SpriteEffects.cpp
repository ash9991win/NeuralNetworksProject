#include"pch.h"
#include "SpriteEffects.h"
#include"Timer.h"
#include"World.h"
#include"Actor.h"
SpriteEffects::~SpriteEffects()
{
}

void SpriteEffects::Update(float deltaTime)
{
}

void SpriteEffects::RestoreToOriginal()
{
	mOwner->mSprite = originalSprite;
	//mOwner->RemoveComponent(*this);
	Enable = false;
}

void SpriteEffects::BeginPlay()
{
	originalSprite = mOwner->mSprite;
	effectTimer = World::CreateTimer(maxDurationOfEffect);
	effectTimer->UpdateDelegate.Bind(&SpriteEffects::Update, this);
	effectTimer->FinishedDelegate.Bind(&SpriteEffects::RestoreToOriginal, this);
	effectTimer->StartTimer();
}

void SpriteEffects::Activate()
{
	if (!Enable)
	{
		effectTimer->StartTimer();
		Enable = true;
	}
}
