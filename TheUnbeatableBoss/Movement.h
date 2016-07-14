#pragma once
#include "ActionComponent.h"
class Movement :
	public Action
{
private:
	Dir CurrentDir;
public:
	Movement(string name);
	~Movement();
	// Inherited via Action
	virtual void Update(float deltaTime) override;
	virtual void BeginPlay() override;
	RTTI_DECLARATION(Movement,Action)
};
class Shoot : public Action
{
public:
	// Inherited via Action
	virtual void Update(float deltaTime) override;
	virtual void BeginPlay() override;
	Shoot(string name) :Action(name) {}
	RTTI_DECLARATION(Shoot,Action)
};
class Shield : public Action
{
public:
	Shield(string name) :Action(name) {}
	// Inherited via Action
	virtual void Update(float deltaTime) override;
	virtual void BeginPlay() override;
	RTTI_DECLARATION(Shield,Action)
};