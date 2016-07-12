#include"pch.h"
#include "Bullet.h"
#include"ResourceManager.h"
#include"CollisionComponent.h"
#include"RigidBody.h"
#include"Boss.h"
RTTI_DEFINITION(Bullet)
void Bullet::Update(float deltaTime)
{
	/*mPosition.x += speed * deltaTime;*/
	if (mPosition.x > WINDOW_WIDTH)
		Destroy();
}

void Bullet::BeginPlay()
{
	mPosition = sf::Vector2f();
	mSprite = *(ResourceManager::LoadSprite("PlayerIdle_1"));
	SetSpriteDimensions(150, 150);
	mSprite.setColor(sf::Color::Blue);

	mCollisionComponent = AddComponent<CollisionComponent>(mSpriteWidth,mSpriteHeight);
	mCollisionComponent->OnCollision.Bind(&Bullet::OnCollision, this);
	rigidBody = AddComponent<RigidBody>();
	rigidBody->SetMass(2.0f);
	speed = 1000;
	rigidBody->AddForce(sf::Vector2f(speed, 0.0f));
}

void Bullet::OnCollision(Actor * actor)
{
	if(actor != this && actor->Is(Boss::TypeIdClass()))
	Destroy();
}
