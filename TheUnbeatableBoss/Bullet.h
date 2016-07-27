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
public:
	Bullet(Actor* owner, Actor* target)
	:mOwner(owner),mTarget(target){

	}
	RigidBody* rigidBody;
	// Inherited via Actor
	virtual void Update(float deltaTime) override;
	virtual void BeginPlay() override;
	void OnCollision(Actor* actor);
	RTTI_DECLARATION(Bullet,Actor)
};

