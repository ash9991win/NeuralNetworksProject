#pragma once
#include "Actor.h"
#include"GeneticAlgorithm.h"
class NeuralNet;
class NeuralTrainer;
class Player;
class Boss :
	public Actor
{
private:
	friend class Player;
	NeuralNet* mComboPredictor;
	NeuralNet* mActionChooser;
	NeuralTrainer* mComboTrainer;
	Player* mPlayer;
	class AnimationComponent* IdleAnimation;
public:
	Boss();
	~Boss();
	void CollidedWithActor(Actor* actor);
	// Inherited via Actor
	void MoveLeft(float deltaTime);
	void MoveRight(float deltaTime);
	void Jump(float deltaTime);
	virtual void Update(float deltaTime) override;
	sf::Keyboard::Key PredictNextKey(vector<double> pattern);
	void CorrectPrediction(sf::Keyboard::Key keyToCorrectTo);
	virtual void BeginPlay() override;
	bool IsBossThinking() const;
	inline NeuralNet* GetBrain() { return mComboPredictor; }
	GeneticAlgorithm<Dir> pathFinder;
#if TRAIN_WITH_DATA
	void TrainBossWithSequence();
#endif
	RTTI_DECLARATION(Boss,Actor)
};

