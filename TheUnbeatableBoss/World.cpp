#include "pch.h"
#include "World.h"
#include "Actor.h"
#include"Component.h"
#include"Timer.h"
std::vector<Actor*> World::mActorTable;
World* World::mWorldInstance;
sf::RenderWindow* World::mWindow;
int World::numberOfCycles;
GAME_STATE World::CURRENT_GAME_STATE;
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
	//mActorTable.erase(std::find(mActorTable.begin(), mActorTable.end(), &actor));
	auto actorToRemove = *(std::find(mActorTable.begin(), mActorTable.end(), &actor));
	if (actorToRemove)
	{
		actorToRemove->isActorAlive = false;
	}
}

void World::UpdateWorld(float deltaTime)
{
	for (auto actor :mActorTable)
	{
		if (actor->shouldUpdate)
		{
			actor->Update(deltaTime);
			for (auto component : actor->mComponents)
			{
				component->Update(deltaTime);
			}
			actor->mSprite.setPosition(actor->mPosition);
			mWindow->draw((actor->mSprite));
		}
	}
	numberOfCycles++;
	if (numberOfCycles > 100)
	{
		auto& index = std::partition(mActorTable.begin(), mActorTable.end(), [](Actor* actor) {return actor->IsActorAlive(); });
		mActorTable.erase(index, mActorTable.end());
		numberOfCycles = 0;
	}
}

void World::BeginWorld()
{
	for (auto* actor : mActorTable)
	{
		actor->BeginPlay();
		for (auto c : actor->mComponents)
		{
			c->BeginPlay();
		}
	}
	numberOfCycles = 0;
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

Timer * World::CreateTimer(float maxTime)
{
	Timer* timer = new Timer(maxTime);
	Timer::mListOfTimers.push_back(timer);
	return timer;
}


World::~World()
{
}
