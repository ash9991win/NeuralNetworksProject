#pragma once
#include"pch.h"
#include "Component.h"
class CollisionComponent :
	public Component
{
protected:
	float mWidth;
	float mHeight;
	sf::Vector2f mPosition;
public:
	CollisionComponent(float width, float height);
	~CollisionComponent();
	typedef delegate<void, Actor*> OnCollisionDelegate;
	OnCollisionDelegate OnCollision;
	// Inherited via Component
	virtual void Update(float deltaTime) override;
	virtual void BeginPlay() override;
	const sf::Vector2f& GetColliderPosition() const;
	RTTI_DECLARATION(CollisionComponent, Component)
};

