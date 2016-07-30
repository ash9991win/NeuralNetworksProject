#pragma once
#include "ActionComponent.h"
#include"ResourceManager.h"
class MoveUp : public Action
{
	// Inherited via Action

public:
	MoveUp(string name)
		:Action(name)
	{
		mDuration = 0.025f;
	}
	virtual void Update(float deltaTime) override;
	virtual void BeginPlay() override;
	RTTI_DECLARATION(MoveUp, Action)
};
class MoveLeft : public Action
{
	// Inherited via Action
public:
	MoveLeft(string name)
		:Action(name)
	{
		mDuration = 0.025f;
	}
	virtual void Update(float deltaTime) override;
	virtual void BeginPlay() override;
	RTTI_DECLARATION(MoveLeft, Action)
};
class MoveRight : public Action
{
	// Inherited via Action
public:
	MoveRight(string name)
		:Action(name)
	{
		mDuration = 0.025f;
	}
	virtual void Update(float deltaTime) override;
	virtual void BeginPlay() override;
	RTTI_DECLARATION(MoveRight, Action)
}; 
class MoveDown : public Action
	{
		// Inherited via Action
	public:
		MoveDown(string name)
			:Action(name)
		{
			mDuration = 0.025f;
		};
		virtual void Update(float deltaTime) override;
		virtual void BeginPlay() override;
		RTTI_DECLARATION(MoveDown, Action)
	};

class Shoot : public Action
{
protected:
	sf::Sprite* mBulletSprite;
	float mDamage;
	float mSpeed;
	Actor* mBulletActor;
	float mFireRate;
public:
	// Inherited via Action
	virtual void Update(float deltaTime) override;
	virtual void BeginPlay() override;
	Shoot(string name) :Action(name) {
		mBulletSprite = ResourceManager::LoadSprite("Bullet1");
		mDuration = 3.0f;
		mFireRate = mDuration;
	}
	RTTI_DECLARATION(Shoot,Action)
};
class Shield : public Action
{
protected:
	sf::Sprite* mShieldSprite; 
	class ShieldActor* mShieldActor;
public:
	Shield(string name) :Action(name) {
		mDuration = 3.0f;
		mShieldSprite = ResourceManager::LoadSprite("Shield");
		mShieldActor = nullptr;
	}

	// Inherited via Action
	virtual void Update(float deltaTime) override;
	virtual void BeginPlay() override;
	RTTI_DECLARATION(Shield,Action)
};