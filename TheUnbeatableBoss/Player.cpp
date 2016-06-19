#include"pch.h"
#include "Player.h"
#include"ResourceManager.h"
#include"InputManager.h"
#include"World.h"
#include"Boss.h"
#include<iostream>
RTTI_DEFINITION(Player)


 void Player::MoveLeft(float d)
{
	mPosition.x -= speed * d ;
	mBoss->MoveLeft(d);
}

void Player::MoveRight(float d)
{
	mPosition.x += speed * d ;
	mBoss->MoveRight(d);
}

void Player::Jump(float d)
{
}

void Player::Update(float dTime)
{
}

void Player::BeginPlay()
{
	InputManager::KeyPressedTable[sf::Keyboard::A].Bind([&](float) {});
	mSprite = *(ResourceManager::LoadSprite("Player0"));
	mPosition = sf::Vector2f(10, WINDOW_HEIGHT - 200);
	SetSpriteDimensions(150,150);
	speed = 1000;
	InputManager::KeyPressedTable[sf::Keyboard::A].Bind(&Player::MoveLeft, this);
	mBoss = World::FindActorsOfType<Boss>()[0];
}
