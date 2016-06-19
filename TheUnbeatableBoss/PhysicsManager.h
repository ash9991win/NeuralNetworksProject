#pragma once
class Actor;
class PhysicsManager
{
	static std::vector<Actor*> ActorsInLevel;
public:
	PhysicsManager();
	~PhysicsManager();
	static void Initialize();
	static void CheckForCollisions();
};

