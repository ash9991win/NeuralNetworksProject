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
	mInputs.reserve(numInputs);
	for (int i = 0; i < numInputs; i++)
	{
		mWeights.push_back(1);
	}
}


double Neuron::Update()
{
	double activationinput = 0.0;
	for (int i = 0; i < mInputs.size(); i++)
	{
		activationinput += (mWeights[i])*(mInputs[i]);
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
	assert(!(index < 0 || index > mNumberOfInputs));
	return mWeights[index];
}

void Neuron::SetWeights(std::vector<double> weights)
{
	mWeights = weights;
}

void Neuron::AssignInput(int index, double value)
{
	if (index >= mInputs.size())
	{
		mInputs.push_back(value);
	}
	else
	{
		mInputs[index] = value;
	}
}

void Neuron::AssignInput(std::vector<double> value)
{
	mInputs = value;
	
}

void Neuron::ChangeInputSize(int newSize)
{
	mWeights.resize(newSize);
}

const std::string & Neuron::Name() const
{
	return mName;
}


