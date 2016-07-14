#include"pch.h"
#include "Boss.h"
#include"ResourceManager.h"
#include"NeuralNet.h"
#include"World.h"
#include"Player.h"
#include"VectorMath.h"
#include"InputManager.h"
#include"AnimationComponent.h"
#include"CollisionComponent.h"
#include"Bullet.h"
#include"PinkGlowEffect.h"
#include"NeuralTrainer.h"
#include"Movement.h"
#include"ActionFactory.h"
#include"PatternChooser.h"
#include<iostream>
#include<future>
#define STORE_PATTERNS 1
using namespace std;
RTTI_DEFINITION(Boss)
Boss::Boss()
{
	mComboPredictor = new NeuralNet();
	mComboTrainer = new NeuralTrainer();
	Neuron* mHiddenToCombo = new Neuron(3, "Player Hidden", ActivationFunctions::Sigmoid);
	Neuron* mHiddenToCombo1 = new Neuron(3, "Player Hidden", ActivationFunctions::Sigmoid);
	Neuron* mHiddenToCombo2 = new Neuron(3, "Player Hidden", ActivationFunctions::Sigmoid);

	Neuron* mOutputCombo = new Neuron(3, "Player Output", ActivationFunctions::Sigmoid);

	NeuronLayer* InputLayer = new NeuronLayer();
	for (int i = 0; i < COMBO_LENGTH; i++)
	{
		Neuron* inputNeuron = new Neuron(1, "Player Inputs", ActivationFunctions::Sigmoid);
		InputLayer->AddNeuron(*inputNeuron);
	}

	NeuronLayer* Hiddenlayer = new NeuronLayer();
	Hiddenlayer->AddNeuron(*mHiddenToCombo);
	Hiddenlayer->AddNeuron(*mHiddenToCombo1);
	Hiddenlayer->AddNeuron(*mHiddenToCombo2);


	NeuronLayer* OutputLayer = new NeuronLayer();
	OutputLayer->AddNeuron(*mOutputCombo);

	mComboPredictor->AssignInputLayer(*InputLayer);
	mComboPredictor->AssignHiddenlayer(*Hiddenlayer);
	mComboPredictor->AssignOutputLayer(*OutputLayer);
	mComboPredictor->Initialize();
	mComboTrainer->AssignNetwork(*mComboPredictor);
	
}


Boss::~Boss()
{
}

void Boss::CollidedWithActor(Actor * actor)
{
	if (actor->Is(Bullet::TypeIdClass()) && actor->IsActorAlive())
	{
		auto pinkeffect = AddComponent<PinkGlowEffect>(0.4);
	}
}

void Boss::MoveLeft(float d)
{
	mPosition.x -= speed * d;
}

void Boss::MoveRight(float d)
{
	mPosition.x += speed * d;
}

void Boss::Jump(float d)
{
}


void Boss::Update(float deltaTime)
{
#if TRAIN_WITH_DATA
	if (InputManager::IsKeyPressed(sf::Keyboard::X))
	{
		TrainBossWithSequence();
	}
#endif
	
}

sf::Keyboard::Key Boss::PredictNextKey(vector<double> inputsToNetwork)
{
	if (inputsToNetwork.size() < 3)
		return sf::Keyboard::BackSpace;
	/*static future<void> neuralThread = std::async(
		[this,inputsToNetwork]() {
			mComboPredictor->AssignInput(inputsToNetwork);
				mComboTrainer->SetExpectedOutput(2.3f);
				auto output = mComboPredictor->Update();
				mComboTrainer->Update();
	}
	);*/
	for (int i = 0; i < inputsToNetwork.size(); i++)
	{
		mComboPredictor->AssignInput(i, inputsToNetwork[i]);
	}
//	mComboPredictor->AssignInput(inputsToNetwork
	vector<double> output;
#if STORE_PATTERNS
	if (!mComboPredictor->CheckIfInputWasCaptured(output))
	{
		output = mComboPredictor->Update();
	}
#else
	output = mComboPredictor->Update();
#endif
	/*else
	{
		cout << "Pattern was already captured" << endl;
	}*/
	//Now we know the output, which can be +- the error rate
	auto& dataSet = mPlayer->mInverseWeights;
	for (auto& i : dataSet)
	{
		if(abs(output[0] - i.first) <= (10 * ERROR_RATE))
			return i.second;
	}
	return sf::Keyboard::Key::BackSpace;
}

void Boss::CorrectPrediction(sf::Keyboard::Key keyToCorrectTo)
{
	vector<double> inputsToNetwork = mPlayer->mInputCombos;
	//mComboPredictor->AssignInput(inputsToNetwork);
	for (int i = 0; i < inputsToNetwork.size(); i++)
	{
		mComboPredictor->AssignInput(i, inputsToNetwork[i]);
	}
	inputsToNetwork.clear();
	mComboTrainer->SetExpectedOutput(mPlayer->mInputWeights[keyToCorrectTo]);
	mComboTrainer->UpdateAsync();
}

void Boss::BeginPlay()
{
	mPosition = sf::Vector2f(WINDOW_WIDTH - 200, WINDOW_HEIGHT - 200);
	SetSpriteDimensions(200, 200);
	speed = 2000;
	mPlayer = World::FindActorsOfType<Player>()[0];
	IdleAnimation = AddComponent<AnimationComponent>();
	IdleAnimation->SetFrames({ "BossIdle_1","BossIdle_2","BossIdle_3","BossIdle_4","BossIdle_5" });
	IdleAnimation->SetFrameDimensions(mSpriteWidth, mSpriteHeight);
	IdleAnimation->SetTimeBetweenFrames(0.24f);
	auto Collider = AddComponent<CollisionComponent>(100,100);
	Collider->OnCollision.Bind(&Boss::CollidedWithActor, this);
	InputManager::KeyReleasedTable[sf::Keyboard::A].Bind(&Boss::MoveLeft, this);
	Patterns = make_shared<BossPattern>(this); 
		for (int i = 0; i < CHROMO_LENGTH; i++)
		{
			Patterns->EnequeAction(ActionFactory::GetARandomAction());
		}
	Patterns->BeginPlay(); 
	mPatternChooser = make_shared<PatternChooser>();
	mPatternChooser->Initialize();
}

bool Boss::IsBossThinking() const
{
	return mComboTrainer->IsTrainerCalculating();
}
#if TRAIN_WITH_DATA
void Boss::TrainBossWithSequence()
{
	vector<vector<double>> inputs;
	vector<vector<double>> outputs;
	for (int i = 0; i < 10; i++)
	{
		vector<double> inputEach;
		vector<double> outputEach;
		for (int j = 0; j < 1; j++)
		{
			inputEach.push_back(ActivationFunctions::Sigmoid(rand()));
			outputEach.push_back(ActivationFunctions::Sigmoid(rand()));
		}
		inputs.push_back(inputEach);
		outputs.push_back(outputEach);
	}
	
	//mComboTrainer->Train(inputs, outputs);
	mComboTrainer->TrainAsync(inputs, outputs);
}
#endif