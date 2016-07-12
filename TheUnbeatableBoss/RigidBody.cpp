#include"pch.h"
#include "RigidBody.h"
#include"Actor.h"


RigidBody::RigidBody()
{
}


RigidBody::~RigidBody()
{
}

void RigidBody::SetMass(float mass)
{
	mMass = mass;
}

void RigidBody::AddForce(sf::Vector2f force)
{
	mForce += force;
}


float RigidBody::CalculateTotalDistanceToTravel()
{
	//For a given force, mass and speed calculate how  much distance should the object travel
	// F = m * a
	// a = v / t
	// d = s * t
	// s = v /t
	// d = 
	return 0.0f;
}

void RigidBody::Update(float deltaTime)
{
	auto acceleration = mForce / mMass;
	mOwner->mPosition += deltaTime * mVelocity;
	mVelocity += deltaTime * acceleration;
}

void RigidBody::BeginPlay()
{
}
