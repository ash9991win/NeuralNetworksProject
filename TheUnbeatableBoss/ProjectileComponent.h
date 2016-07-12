#pragma once
#include "Component.h"
class ProjectileComponent :
	public Component
{
private:
	float mMass;
	sf::Vector2f mVelocity;
	sf::Vector2f mInitialVelocity;
	sf::Vector2f mForce;
	const float GRAVITY = 9.8f;
	float mLaunchAngle;
public:
	ProjectileComponent();
	~ProjectileComponent();
	// Inherited via Component
	virtual void Update(float deltaTime) override;
	void SetLaunchAngle(float angle);
	virtual void BeginPlay() override;
};

