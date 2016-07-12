#include"pch.h"
#include "CollisionManager.h"
#include"World.h"
#include"CollisionComponent.h"
#include"Actor.h"
#include"StaticActor.h"
void CollisionManager::Update(float deltaTime)
{
	//get all the actors in the world with collision components
	auto mActorsWithColliders = World::GetAllActorsInTheWorld();
	//For each actor, check with all the other actors for a collision
	for (auto actor1 : mActorsWithColliders)
	{
		auto Collider1 = actor1->GetComponent<CollisionComponent>();
		if (Collider1)
		{
			for (auto actor2 : mActorsWithColliders)
			{
				auto Collider2 = actor2->GetComponent<CollisionComponent>();
				if (actor1 != actor2 && Collider2)
				{
					if (Collider1->mPosition.x < Collider2->mPosition.x + Collider2->mWidth &&
						Collider1->mPosition.x + Collider1->mWidth > Collider2->mPosition.x &&
						Collider1->mPosition.y < Collider2->mPosition.y + Collider2->mHeight &&
						Collider1->mHeight + Collider1->mPosition.y > Collider2->mPosition.y) {
						// collision detected!
						Collider1->OnCollision.Invoke(actor2);
						Collider2->OnCollision.Invoke(actor1);
					}
				}
			}
		}
	}
}

CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}
