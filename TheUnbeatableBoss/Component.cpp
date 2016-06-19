#include"pch.h"
#include "Component.h"

void Component::SetOwner(Actor & owner)
{
	mOwner = &owner;
}


Component::Component()
{
}


Component::~Component()
{
}
