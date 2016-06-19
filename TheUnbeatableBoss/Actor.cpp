#include "Actor.h"
#include"pch.h"
#include "Actor.h"
#include"World.h"
Actor::~Actor()
{
	World::UnRegister(*this);
}

const World * Actor::GetWorld() const
{
	return mWorld;
}

void Actor::SetSpriteDimensions(float width, float height)
{
	mSpriteWidth = width;
	mSpriteHeight = height;
	mSprite.setScale(mSpriteWidth / mSprite.getLocalBounds().width, mSpriteHeight / mSprite.getLocalBounds().height);
}



