#pragma once
#include "Actor.h"
class CollisionComponent;
class RigidBody;
class Bullet :
	public Actor
{
public:
	RigidBody* rigidBody;
	// Inherited via Actor
	virtual void Update(float deltaTime) override;
	virtual void BeginPlay() override;
	void OnCollision(Actor* actor);
	CollisionComponent* mCollisionComponent;
	RTTI_DECLARATION(Bullet,Actor)
};

