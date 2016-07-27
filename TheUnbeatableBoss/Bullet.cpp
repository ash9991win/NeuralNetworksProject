#include"pch.h"
#include "Bullet.h"
#include"ResourceManager.h"
#include"CollisionComponent.h"
#include"RigidBody.h"
#include"Boss.h"
#include"VectorMath.h"

RTTI_DEFINITION(Bullet)
void Bullet::Update(float deltaTime)
{
	/*mPosition.x += speed * deltaTime;*/
	if (mPosition.x > WINDOW_WIDTH)
		Destroy();
}

void Bullet::BeginPlay()
{
	mSprite = *(ResourceManager::LoadSprite("PlayerIdle_1"));
	SetSpriteDimensions(150, 150);
	mSprite.setColor(sf::Color::Blue);

	CreateCollider();
	mCollider->OnCollision.Bind(&Bullet::OnCollision, this);
	rigidBody = AddComponent<RigidBody>();
	rigidBody->SetMass(2.0f);
	speed = 1000;
	mPosition = mOwner->mPosition;
	sf::Vector2f directionVector = mTarget->mPosition - mOwner->mPosition;
	VectorMath::Normalize(directionVector);
	directionVector *= speed;
	rigidBody->AddForce(directionVector);
}

void Bullet::OnCollision(Actor * actor)
{
	if(actor != this && (actor != mOwner) && (actor == mTarget))
	Destroy();
}
