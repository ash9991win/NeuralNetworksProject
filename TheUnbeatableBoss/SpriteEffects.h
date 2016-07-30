#pragma once
#include "Component.h"
class Timer;
class SpriteEffects :
	public Component
{
private:
	float maxDurationOfEffect;
	Timer* effectTimer;
	sf::Sprite originalSprite;
public:
	SpriteEffects(float maxtime) : maxDurationOfEffect(maxtime)
	{
		Enable = true;
	}
	~SpriteEffects();
	// Inherited via Component
	virtual void Update(float deltaTime) override;
	void RestoreToOriginal();
	virtual void BeginPlay() override;
	virtual void Activate();
	void ChangeDuration(float newDur) { maxDurationOfEffect = newDur; }
};

