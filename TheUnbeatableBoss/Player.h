#pragma once
#include "Actor.h"
class Boss;
/*!
\class Player
\brief The Player class
*/
class Player :
	public Actor
{
public:
	/*!
	\var Boss* mBoss
	\brief The reference to the boss in the world
	*/
	Boss* mBoss;
	Player() = default;
	~Player() = default;
	/*!
	\fn MoveLeft(float)
	\brief The function to make the player move left
	\param The time period between frames
	*/
	void MoveLeft(float d);
	/*!
	\fn MoveRight(float)
	\brief The function to make the player move right
	\param The time period between frames
	*/
	void MoveRight(float d);
	/*!
	\fn Jump(float)
	\brief The function to make the player jump
	\param The time period between frames
	*/
	void Jump(float d);
	// Inherited via Actor
	virtual void Update(float deltaTime) override;
	virtual void BeginPlay() override;
	RTTI_DECLARATION(Player,Actor)
};

