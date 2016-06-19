#pragma once
#include"pch.h"
class Actor;
/*
\class World
\brief The game world
*/
class World
{
private:
	static std::vector<Actor*> mActorTable;
	static World* mWorldInstance;
	static sf::RenderWindow* mWindow;
	static void RegisterActor(Actor& actor);
public:
	/*
	\fn CreateWorld(sf::RenderWindow*)
	\brief Creates the world 
	\param The window of the game
	*/
	static void CreateWorld(sf::RenderWindow* window);
	/*
	\fn SpawnActor(std::string)
	\brief Spawns an actor of a given type
	\param The name of the actor to be set
	*/
	template<typename T>
	static T* SpawnActor(std::string actorName);
	/*
	\fn UnRegister(Actor&)
	\brief Unregisters an actor 
	\param The actor to be unregistered
	*/
	static void UnRegister(Actor& actor);
	/*
	\fn UpdateWorld(float)
	\brief Updates the world with the elapsed time
	\param The elapsed time
	*/
	static void UpdateWorld(float deltaTime);
	/*
	\fn BeginWorld()
	\brief Initializes the world
	*/
	static void BeginWorld();
	/*
	\fn FindActorsOfType()
	\brief Finds all actors of the given type
	\return A vector of all the actors found
	*/
	template<typename T>
	static std::vector<T*> FindActorsOfType();
	/*
	\fn FindActorsOfType()
	\brief Finds all actors of the given type
	\return A vector of all the actors found
	*/
	static std::vector<Actor*> FindActorsOfType(std::uint64_t type);
	/*
	\fn GetAllActorsInTheWorld()
	\brief Finds all actors in the world
	\return A vector of all the actors 
	*/
	static const std::vector<Actor*> GetAllActorsInTheWorld();
	World();
	~World();
};

template<typename T>
inline T * World::SpawnActor(std::string actorName)
{
	T* actorCreated = new T();
	actorCreated->mName = actorName;
	RegisterActor(*actorCreated);
	return actorCreated;
}

template<typename T>
inline std::vector<T*> World::FindActorsOfType()
{
	std::vector<T*> result;
	for (auto actors : mActorTable)
	{
		if (actors->Is(T::TypeIdClass()))
		{
			result.push_back(actors->As<T>());
		}
	}
	return result;
}
