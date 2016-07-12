#pragma once
#include "SpriteEffects.h"
class PinkGlowEffect :
	public SpriteEffects
{
public:
	virtual void Update(float deltaTime) override;
	PinkGlowEffect(float d);
	~PinkGlowEffect();
};

