#include"pch.h"
#include "PhysicsManager.h"
#include "World.h"
#include"Actor.h"
#include"CollisionComponent.h"
std::vector<Actor*> PhysicsManager::ActorsInLevel;
PhysicsManager::PhysicsManager()
{
}


PhysicsManager::~PhysicsManager()
{
}

void PhysicsManager::Initialize()
{
	auto actors = World::GetAllActorsInTheWorld();
	for (auto ac : actors)
	{
		if (ac->GetComponent<CollisionComponent>())
		{
			ActorsInLevel.push_back(ac);
		}
	}
}

void PhysicsManager::CheckForCollisions()
{
	for (int i = 0; i < ActorsInLevel.size(); i++)
	{
		for (int j = 0; j < ActorsInLevel.size(); j++)
		{
			CollisionComponent* c1 = ActorsInLevel[i]->GetComponent<CollisionComponent>();
			CollisionComponent* c2 = ActorsInLevel[j]->GetComponent<CollisionComponent>();
			if (ActorsInLevel[i] != ActorsInLevel[j])
			{
				//Check for collision, then invoke 
				auto actor1 = ActorsInLevel[i];
				auto actor2 = ActorsInLevel[j];
				c1->OnCollision.Invoke(std::forward<Actor*>(actor1));
				c2->OnCollision.Invoke(std::forward<Actor*>(actor2));

			}
		}
	}
}
