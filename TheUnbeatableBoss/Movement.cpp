#include"pch.h"
#include "Movement.h"


RTTI_DEFINITION(Movement);
RTTI_DEFINITION(Shoot);
RTTI_DEFINITION(Shield)
Movement::Movement(string name)
	:Action(name)
{
}


Movement::~Movement()
{
}

void Movement::Update(float deltaTime)
{

}

void Movement::BeginPlay()
{
	CurrentDir = (Dir)(RandInt(1, 3));
}

void Shoot::Update(float deltaTime)
{
}

void Shoot::BeginPlay()
{
}

void Shield::Update(float deltaTime)
{
}

void Shield::BeginPlay()
{
}
