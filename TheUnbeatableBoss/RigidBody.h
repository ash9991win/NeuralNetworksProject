#pragma once
#include "Component.h"
class RigidBody :
	public Component
{
private:
	friend class CollisionManager;
	float mMass;
	sf::Vector2f mVelocity;
	sf::Vector2f mForce;
	sf::Vector2f mAcceleration;
	float mDistanceTravelled;
	sf::Vector2f mNewPosition;
	bool hasHitFloor;
	void HasHitFloor()
	{
		mForce.y = 0;
	}
public:
	RigidBody();
	~RigidBody();

	// Inherited via Component
	void SetMass(float mass = 1.0f);
	void ResetForce() {
		mForce = mVelocity = sf::Vector2f();
	//	mForce.y = 9.8 * mMass;
		mDistanceTravelled = 0;
	}
	void AddForce(sf::Vector2f force);
	void SetForce(sf::Vector2f force) { mForce = force; mDistanceTravelled = 0; };
	void SetForce(float xForce, float yForce) {  mForce = sf::Vector2f(xForce, yForce); }
	sf::Vector2f& GetForce() { return mForce; };
	float CalculateTotalDistanceToTravel();
	virtual void Update(float deltaTime) override;
	virtual void BeginPlay() override;
};

