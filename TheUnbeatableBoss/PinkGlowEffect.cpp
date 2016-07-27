#include"pch.h"
#include "PinkGlowEffect.h"
#include"Actor.h"


void PinkGlowEffect::Update(float deltaTime)
{
	SpriteEffects::Update(deltaTime);
	mOwner->mSprite.setColor(sf::Color::Red);
}

PinkGlowEffect::PinkGlowEffect(float d)
	:SpriteEffects(d)
{
}

PinkGlowEffect::~PinkGlowEffect()
{
}
