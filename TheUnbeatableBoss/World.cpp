#include "pch.h"
#include "World.h"
#include "Actor.h"
#include"Component.h"
std::vector<Actor*> World::mActorTable;
World* World::mWorldInstance;
sf::RenderWindow* World::mWindow;
void World::CreateWorld(sf::RenderWindow* window)
{
	mWorldInstance = new World();
	mWindow = window;
}

void World::RegisterActor(Actor& actor)
{
	mActorTable.push_back(&actor);
	actor.mWorld = mWorldInstance;
	actor.mWindow = mWindow;
}

void World::UnRegister(Actor & actor)
{
	mActorTable.erase(std::find(mActorTable.begin(), mActorTable.end(), &actor));
}

void World::UpdateWorld(float deltaTime)
{
	for (auto actor :mActorTable)
	{
		actor->Update(deltaTime);
		for (auto& component : actor->mComponents)
		{
			component->Update(deltaTime);
		}
		actor->mSprite.setPosition(actor->mPosition);
		mWindow->draw((actor->mSprite));
	}
}

void World::BeginWorld()
{
	for (auto* actor : mActorTable)
	{
		actor->BeginPlay();
	}
}

std::vector<Actor*> World::FindActorsOfType(std::uint64_t type)
{
	std::vector<Actor*> actorsOfThatType;
	for (auto actors : mActorTable)
	{
		if (actors->Is(type))
		{
			actorsOfThatType.push_back(actors);
		}
	}
	return actorsOfThatType;
}

const std::vector<Actor*> World::GetAllActorsInTheWorld()
{
	return mActorTable;
}

World::World()
{
}


World::~World()
{
}
