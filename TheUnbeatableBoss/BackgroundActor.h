#pragma once
#include "Actor.h"
class BackgroundActor :
	public Actor
{
public:
	BackgroundActor();
	~BackgroundActor();

	// Inherited via Actor
	virtual void Update(float deltaTime) override;
	virtual void BeginPlay() override;
};

