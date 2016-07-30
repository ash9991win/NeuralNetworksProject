#pragma once
#include "Actor.h"
class CollisionComponent;
class RigidBody;
class Bullet :
	public Actor
{
private:
	Actor* mOwner;
	Actor* mTarget;
	double mDamage;
public: 
	Bullet(Actor* owner, Actor* target,sf::Sprite& sprite, float width, float height,float sp,double damage = 10)
	:mOwner(owner),mTarget(target),mDamage(damage){
		speed = sp;
		mSprite = sprite;
		SetSpriteDimensions(width, height);
	}
	RigidBody* rigidBody;
	// Inherited via Actor
	virtual void Update(float deltaTime) override;
	virtual void BeginPlay() override;
	void OnCollision(Actor* actor);
	RTTI_DECLARATION(Bullet,Actor)
};

