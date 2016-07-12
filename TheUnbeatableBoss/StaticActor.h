#pragma once
#include"Actor.h"
class CollisionComponent;
class StaticActor : public Actor
{
public:
	StaticActor(const float width,const float height);
	// Inherited via Actor
	virtual void Update(float deltaTime) override;
	virtual void OnCollision(Actor* other);
	virtual void BeginPlay() override;
	CollisionComponent* mCollider;
	RTTI_DECLARATION(StaticActor,Actor)
	// Inherited via Actor
};

