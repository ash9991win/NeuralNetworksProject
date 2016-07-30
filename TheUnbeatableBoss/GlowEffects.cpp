#include"pch.h"
#include "GlowEffects.h"
#include"Actor.h"


void GlowEffects::Update(float deltaTime)
{
	SpriteEffects::Update(deltaTime);
	mOwner->mSprite.setColor(mGlowColor);
}

GlowEffects::GlowEffects(float d,sf::Color color)
	:SpriteEffects(d),mGlowColor(color)
{
}

GlowEffects::~GlowEffects()
{
}
