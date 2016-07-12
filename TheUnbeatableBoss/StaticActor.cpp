#include "pch.h"
#include "StaticActor.h"
#include"CollisionComponent.h"

RTTI_DEFINITION(StaticActor)
StaticActor::StaticActor(const float width,const float height)
{
	mSpriteWidth = width;
	mSpriteHeight = height;
	shouldUpdate = false;
}

void StaticActor::Update(float deltaTime)
{
}

void StaticActor::OnCollision(Actor * other)
{
}

void StaticActor::BeginPlay()
{
	mCollider = AddComponent<CollisionComponent>(mSpriteWidth,mSpriteHeight);
}
