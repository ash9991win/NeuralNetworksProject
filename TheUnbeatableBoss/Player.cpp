#include"pch.h"
#include "Player.h"
#include"ResourceManager.h"
#include"InputManager.h"
#include"World.h"
#include"Boss.h"
#include"AnimationComponent.h"
#include"AnimationManager.h"
#include"Bullet.h"
#include"RigidBody.h"
#include"ProjectileComponent.h"
#include"Timer.h"
#include"StaticActor.h"
#include"CollisionComponent.h"
#include"NeuralTrainer.h"
#include<iostream>
#include<list>
RTTI_DEFINITION(Player)


void Player::UpdateInputPresses(sf::Keyboard::Key key,string name)
{
	mNumberOfKeyPresses++;
	if (mBossPredictedAValue && mBossPrediction == key && mNumberOfKeyPresses == (COMBO_LENGTH + 1))
	{
		cout << "Correct prediction of "<<name<<"!" << endl;
		mBossPredictedAValue = false;
		mInputCombos.clear();
		mNumberOfKeyPresses = 0;
	}
	else if (mBossPredictedAValue && mBossPrediction != key && mNumberOfKeyPresses == (COMBO_LENGTH + 1))
	{
		cout << "Should have  predicted "<<name << endl;
		mBossPredictedAValue = false;
		mBoss->CorrectPrediction(key);
		mInputCombos.clear();
		mNumberOfKeyPresses = 0;
	}
	if (mNumberOfKeyPresses <= COMBO_LENGTH)
	{
		mInputCombos.push_back(mInputWeights[key]);
	}
}

void Player::MoveLeft(float d)
{
	AnimManager->PlayAnimation(AnimationID::PlayerLeftWalkAnimation);
	//mPosition.x -= speed * d ;
	if(mIsJumpingUp)
		mRigidBody->AddForce(sf::Vector2f(-speed, 0));
	mRigidBody->SetForce(sf::Vector2f(-speed, 0));

}

void Player::MoveRight(float d)
{
//	WalkAnimation->autoPlay = true;
	AnimManager->PlayAnimation(AnimationID::PlayerRightWalkAnimation);
	/*mPosition.x += speed * d ;*/
	mRigidBody->SetForce(sf::Vector2f(speed, 0));

}

void Player::Jump(float d)
{
	if (!mIsJumpingUp)
	{
		mRigidBody->AddForce(sf::Vector2f(0, -speed));
		mIsJumpingUp = true;
		mOldPosition = mPosition;
	}
}

void Player::Shoot(float d)
{
 	auto bullet = World::SpawnActor<Bullet>("Bullet");
	cout << "Added bullet" << endl;
	bullet->mPosition = mPosition;
	bullet->speed = 2000;
}

void Player::Update(float dTime)
{
	if (mIsJumpingUp)
	{
		distanceTravelled = abs(mOldPosition.y - mPosition.y);
		//If the player is jumping, then once the distance has been travelled, set the force to positive speed
		if (distanceTravelled >= MAX_JUMP_DISTANCE)
		{
			mIsJumpingUp = false;
			mIsJumpingDown = true;
			mRigidBody->SetForce(sf::Vector2f(0, speed));
			mOldPosition = mPosition;
			distanceTravelled = 0;
		}
	}
	if (mPosition.y + mSpriteHeight >= FLOOR_Y && !mIsJumpingUp)
	{
		mRigidBody->SetForce(mRigidBody->GetForce().x, 0);
	}
	if (mNumberOfKeyPresses == COMBO_LENGTH)
	{
	//	mNumberOfKeyPresses = 0;
		auto result = mBoss->PredictNextKey(mInputCombos);
		mBossPredictedAValue = true;
		if (result != sf::Keyboard::Key::BackSpace)
		{
			cout << "Predicted "<<result << endl;
			mBossPrediction = result;
			//mInputCombos.clear();
			mInputCombos.clear();
		}
	}
	if (mInputCombos.size() > COMBO_LENGTH)
		mInputCombos.clear();
}

void Player::BeginPlay()
{
	mShouldBossCorrectPrediction = false;
	mPosition = sf::Vector2f(10, WINDOW_HEIGHT - 200);
	mOldPosition = mPosition;
	mIsJumpingUp = false;
	mIsJumpingDown = false;
	SetSpriteDimensions(150,150);
	speed = 1000;
	InputManager::KeyPressedTable[sf::Keyboard::A].Bind(&Player::MoveLeft, this);
	InputManager::KeyReleasedTable[sf::Keyboard::D].Bind([this](float d) {AnimManager->PlayAnimation(AnimationID::PlayerIdleAnimation); mRigidBody->ResetForce();
	
	UpdateInputPresses(sf::Keyboard::D, "D");
	});
	InputManager::KeyReleasedTable[sf::Keyboard::A].Bind([this](float d) {AnimManager->PlayAnimation(AnimationID::PlayerIdleAnimation); mRigidBody->ResetForce();
	UpdateInputPresses(sf::Keyboard::A, "A");
	}
	);
	InputManager::KeyReleasedTable[sf::Keyboard::Space].Bind([this](float d) {
	UpdateInputPresses(sf::Keyboard::Space, "Space");
	}
	);
	InputManager::KeyReleasedTable[sf::Keyboard::LShift].Bind([this](float d) {
		UpdateInputPresses(sf::Keyboard::LShift, "LShift");
	}
	);
	InputManager::KeyPressedTable[sf::Keyboard::D].Bind(&Player::MoveRight, this);
	InputManager::KeyPressedTable[sf::Keyboard::LShift].Bind(&Player::Shoot,this);
	InputManager::KeyPressedTable[sf::Keyboard::Space].Bind(&Player::Jump, this);

	mInputWeights[sf::Keyboard::A] = ActivationFunctions::Sigmoid(-1);
	mInputWeights[sf::Keyboard::D] = ActivationFunctions::Sigmoid(1);
	mInputWeights[sf::Keyboard::Space] = ActivationFunctions::Sigmoid(0);
	mInputWeights[sf::Keyboard::LShift] = ActivationFunctions::Sigmoid(0.5);

	for (auto pair : mInputWeights)
	{
		mInverseWeights[pair.second] = pair.first;
	}
	mBoss = World::FindActorsOfType<Boss>()[0];
	mBoss->mComboTrainer->FinishedCalculationEvent.Bind([this]() {mInputCombos.clear(); });
	AnimManager = AddComponent<AnimationManager>();
	AnimManager->PlayAnimation(AnimationID::PlayerIdleAnimation);
	mRigidBody = AddComponent<RigidBody>();
	mRigidBody->SetMass(2.0f);
	
	auto collider = AddComponent<CollisionComponent>(mSpriteWidth, mSpriteHeight);
	collider->OnCollision.Bind(&Player::OnCollision, this);
}

void Player::OnCollision(Actor * other)
{
	if (other->Is(Boss::TypeIdClass()))
	{

	}
	else if(other->Is(StaticActor::TypeIdClass()))
	{
		if (mIsJumpingDown)
		{
			cout << "Collided with floor" << endl;
			mRigidBody->ResetForce();
			mIsJumpingDown = false;
		}
	}
}
