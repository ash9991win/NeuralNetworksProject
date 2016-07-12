#include"pch.h"
#include "Actor.h"
Actor::~Actor()
{
	World::UnRegister(*this);
}

const World * Actor::GetWorld() const
{
	return mWorld;
}

void Actor::Update(float deltaTime)
{
}

void Actor::RemoveComponent(Component & comp)
{
	mComponents.erase(std::find(mComponents.begin(), mComponents.end(), &comp));
}

void Actor::SetSpriteDimensions(float width, float height)
{
	mSpriteWidth = width;
	mSpriteHeight = height;
	mSprite.setScale(mSpriteWidth / mSprite.getLocalBounds().width, mSpriteHeight / mSprite.getLocalBounds().height);
}

void Actor::Destroy()
{
	World::UnRegister(*this);
}



