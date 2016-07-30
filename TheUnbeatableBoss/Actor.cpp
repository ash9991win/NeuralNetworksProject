#include"pch.h"
#include "Actor.h"
#include"CollisionComponent.h"
#include"GlowEffects.h"
void Actor::CreateCollider()
{
	mCollider =  new CollisionComponent(mSpriteWidth,mSpriteHeight);
}
void Actor::Shield()
{
	GlowComponent->SetColor(sf::Color::Blue);
	//Keep moving up
     GlowComponent->Activate();
	 IsShielded = true;
}
void Actor::UnShield()
{
	GlowComponent->Enable = false;
	IsShielded = false;
}
void Actor::GameOver()
{
}
void Actor::Damage(double value)
{
	mHealth -= value;
	if (mHealth <= 0)
	{
		GameOver();
	}
}
Actor::~Actor()
{
	World::UnRegister(*this);
	if (mCollider)
		delete mCollider;
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



