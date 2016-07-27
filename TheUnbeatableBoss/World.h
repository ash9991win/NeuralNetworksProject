#pragma once
class Actor;
class Timer;
/*
\class World
\brief The game world
*/

enum class GAME_STATE
{
	GAME_STARTED, GAME_RUNNING, GAME_PAUSED, GAME_EXIT
};
class World
{
private:
	//Holds all the actors in the level
	static std::vector<Actor*> mActorTable;
	//Hold one instance for the game 
	static World* mWorldInstance;
	//The window that the world will be working on
	static sf::RenderWindow* mWindow;
	//Register an actor into the world
	static void RegisterActor(Actor& actor);
	//An actor can be destroyed at any point in the game, which means going through the list of 
	//actors and deleting them every frame is very expensive. So I have a number of cycles that 
	//I wait before proceeding to delete the destroyed actors
	static int numberOfCycles;
	//Constructor is private
	World();
public:
	static GAME_STATE CURRENT_GAME_STATE;
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
	template<typename T,typename...arg>
	static T* SpawnActor(std::string actorName,arg...);
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
	static const std::vector<Actor*>& GetAllActorsInTheWorld();
	static Timer* CreateTimer(float maxTime);
	~World();
};

template<typename T,typename...arg>
inline T * World::SpawnActor(std::string actorName,arg...a)
{
	
	T* actorCreated = new T(a...);
	actorCreated->mName = actorName;
	actorCreated->shouldUpdate = true;
	actorCreated->isActorAlive = true;
	if (CURRENT_GAME_STATE == GAME_STATE::GAME_RUNNING)
	{
		actorCreated->BeginPlay();
	}
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
