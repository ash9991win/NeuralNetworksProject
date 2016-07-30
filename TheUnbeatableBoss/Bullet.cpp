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
	
	CreateCollider();
	mCollider->SetOwner(*this);
	mCollider->OnCollision.Bind(&Bullet::OnCollision, this);
	rigidBody = AddComponent<RigidBody>();
	rigidBody->SetMass(2.0f);
	mPosition = mOwner->mPosition;
	mPosition.y += (mOwner->mSpriteHeight / 2);
	sf::Vector2f directionVector = mTarget->mPosition - mOwner->mPosition;
	VectorMath::Normalize(directionVector);
	directionVector *= speed;
	rigidBody->AddForce(directionVector);
}

void Bullet::OnCollision(Actor * actor)
{
	if (actor != this && (actor != mOwner) && (actor == mTarget))
	{
		Destroy();
		mTarget->Damage(mDamage);

	}
}
