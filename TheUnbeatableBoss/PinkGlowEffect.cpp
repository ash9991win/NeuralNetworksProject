#include"pch.h"
#include "PinkGlowEffect.h"
#include"Actor.h"


void PinkGlowEffect::Update(float deltaTime)
{
	mOwner->mSprite.setColor(sf::Color::Red);
}

PinkGlowEffect::PinkGlowEffect(float d)
	:SpriteEffects(d)
{
}

PinkGlowEffect::~PinkGlowEffect()
{
}
