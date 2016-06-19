#pragma once
#include "Actor.h"
class NeuralNet;
class Player;
class Boss :
	public Actor
{
private:
	NeuralNet* mBrain;
	Player* mPlayer;
public:
	Boss();
	~Boss();

	// Inherited via Actor
	void MoveLeft(float deltaTime);
	void MoveRight(float deltaTime);
	void Jump(float deltaTime);
	virtual void Update(float deltaTime) override;
	virtual void BeginPlay() override;
	inline NeuralNet* GetBrain() { return mBrain; }
	RTTI_DECLARATION(Boss,Actor)
};

