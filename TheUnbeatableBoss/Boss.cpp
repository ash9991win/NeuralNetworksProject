#include"pch.h"
#include "Boss.h"
#include"ResourceManager.h"
#include"NeuralNet.h"
#include"World.h"
#include"Player.h"
#include"VectorMath.h"
#include"InputManager.h"
#include<iostream>
RTTI_DEFINITION(Boss)
Boss::Boss()
{
	mBrain = new NeuralNet();
	Neuron* neuron = new Neuron(2, "PlayerInputs", [](double i) {if (i > 0.0) { return i; } else { return 0.0; } });
	Neuron* neuronI = new Neuron(2, "PlayerInputs", [](double i) {if (i > 0.0) { return i; } else { return 0.0; } });

	NeuronLayer* inputLayer = new NeuronLayer();
	inputLayer->AddNeuron(*neuron);
	inputLayer->AddNeuron(*neuron);
	inputLayer->AddNeuron(*neuron);
	inputLayer->AddNeuron(*neuron);

	inputLayer->AddNeuron(*neuron);
	Neuron *neuron1 = new Neuron(5,"PlayerDistance", [](double i) {if (i > 0.0) { return i; }else { return 0.0; } });
	Neuron *neuronH = new Neuron(5, "PlayerDistance", [](double i) {if (i > 0.0) { return i; } else { return 0.0; } });
	NeuronLayer* hiddenLayer = new NeuronLayer();
	hiddenLayer->AddNeuron(*neuron1);
	hiddenLayer->AddNeuron(*neuronH);
	hiddenLayer->AddNeuron(*neuronH);
	hiddenLayer->AddNeuron(*neuronH);

	Neuron* neuron2 = new Neuron(6,"WorldState", [](double i) {if (i > 0.0) { return i; }else { return 0.0; } });
	NeuronLayer* outputLayer = new NeuronLayer();
	outputLayer->AddNeuron(*neuron2);
	outputLayer->AddNeuron(*neuron2);
	outputLayer->AddNeuron(*neuron2);
	outputLayer->AddNeuron(*neuron2);
	outputLayer->AddNeuron(*neuron2);

	mBrain->AssignInputLayer(*inputLayer);
	mBrain->AssignHiddenlayer(*hiddenLayer);
	mBrain->AssignOutputLayer(*outputLayer);
}


Boss::~Boss()
{
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
	static vector<double> inputsToTheBrain;
	static int numberOfKeyPresses = 0;
	double distance = VectorMath::Distance(mPosition, mPlayer->mPosition);
	if (InputManager::IsKeyPressed(sf::Keyboard::A))
	{
		inputsToTheBrain.push_back(2);
		std::cout << "A pressed" << endl;
		numberOfKeyPresses++;
	}
	if (InputManager::IsKeyPressed(sf::Keyboard::D))
	{
		inputsToTheBrain.push_back(3);
		std::cout << "D pressed" << endl;
		numberOfKeyPresses++;
	}
	
	if (inputsToTheBrain.size() && numberOfKeyPresses >= 4)
	{
		auto output = mBrain->Update(inputsToTheBrain);
		cout << output[0] << endl;
		inputsToTheBrain.clear();
		numberOfKeyPresses = 0;
	}
}

void Boss::BeginPlay()
{
	mSprite = *(ResourceManager::LoadSprite("Boss0"));
	mPosition = sf::Vector2f(WINDOW_WIDTH - 200, WINDOW_HEIGHT - 200);
	SetSpriteDimensions(200, 200);
	speed = 2000;
	mPlayer = World::FindActorsOfType<Player>()[0];

}
