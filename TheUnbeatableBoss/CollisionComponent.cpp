#include"pch.h"
#include "CollisionComponent.h"
#include"Actor.h"
RTTI_DEFINITION(CollisionComponent)
CollisionComponent::CollisionComponent(float width, float height)
	:mWidth(width),mHeight(height)
{
}

CollisionComponent::~CollisionComponent()
{
}

void CollisionComponent::Update(float deltaTime)
{
	mPosition = mOwner->mPosition;
}

void CollisionComponent::BeginPlay()
{
}

const sf::Vector2f & CollisionComponent::GetColliderPosition() const
{
	return mPosition;
}
