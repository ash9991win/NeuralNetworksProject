#include"pch.h"
#include "Component.h"

Component::~Component()
{
}

void Component::SetOwner(Actor & owner)
{
	mOwner = &owner;
}