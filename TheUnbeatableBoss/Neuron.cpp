#include"pch.h"
#include "Neuron.h"
#include"Primitive.h"
#include<random>
#include<assert.h>
using namespace std;



Neuron::Neuron(int numInputs,const std::string& name, std::function<double(double)> activation)
	:mName(name),mActivationFunction(activation),mNumberOfInputs(numInputs)
{
	mWeights.reserve(numInputs);
}


double Neuron::Update()
{
	double activationinput = 0.0;
	for (auto i : mWeights)
	{
		activationinput += i;
	}
	mOutput =  mActivationFunction(activationinput);
	return mOutput;
}

void Neuron::SetWeight(int index, double weight)
{
	if (index < 0 || index > mNumberOfInputs)
	{
		return;
	}
	mWeights[index] = weight;
}

double Neuron::GetWeight(int index)
{
	assert(index < 0 || index > mNumberOfInputs);
	return mWeights[index];
}

void Neuron::SetWeights(std::vector<double> weights)
{
	mWeights = weights;
}

void Neuron::ChangeInputSize(int newSize)
{
	mWeights.resize(newSize);
}

const std::string & Neuron::Name() const
{
	return mName;
}


