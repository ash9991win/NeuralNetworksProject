#pragma once
#include "Actor.h"
class Boss;
class RigidBody;
/*!
\class Player
\brief The Player class
*/
class Action;
class Player :
	public Actor
{
private:
	bool mIsJumpingUp;
	bool mIsJumpingDown;
	sf::Vector2f mOldPosition;
	float distanceTravelled;
	const float MAX_JUMP_DISTANCE = 50;
	bool mShouldBossCorrectPrediction;
	sf::Keyboard::Key mBossPrediction;
	bool mBossPredictedAValue;
	int mNumberOfKeyPresses;
	void UpdateInputPresses(sf::Keyboard::Key key, string name); \
	shared_ptr<Action> mCurrentAction;
	void InitializeAction();
public:
	map<sf::Keyboard::Key,double> mInputWeights;
	vector<double> mInputCombos;
	map<double, sf::Keyboard::Key> mInverseWeights;
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
	void Shoot(float d);
	virtual void Update(float deltaTime) override;
	virtual void BeginPlay() override;
	virtual void Damage(double value) override;
	class AnimationManager* AnimManager;
	void OnCollision(Actor* other);
	RigidBody* mRigidBody;
	//class AnimationComponent* IdleAnimation;
	//class AnimationComponent* WalkAnimation;
	RTTI_DECLARATION(Player,Actor)
};

