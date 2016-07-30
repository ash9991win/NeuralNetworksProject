#include"pch.h"
#include "ActionComponent.h"
#include"ActionFactory.h"

RTTI_DEFINITION(Action)
Action::Action(string name)
	:mName(name)
{
	mEffectiveness = 0.0;

}


Action::~Action()
{
}

void Action::Update(float deltaTime)
{
}

void Action::BeginPlay()
{
	mEffectiveness = 0.0;
}
