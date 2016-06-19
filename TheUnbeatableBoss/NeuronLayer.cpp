#include"pch.h"
#include "NeuronLayer.h"
using namespace std;



void NeuronLayer::AddNeuron(Neuron & newNeuron)
{
	mNeurons.push_back(&newNeuron);
	mNumNeurons++;
}

void NeuronLayer::RemoveNeuron(Neuron & neuron)
{
	mNeurons.erase(std::find(mNeurons.begin(), mNeurons.end(), &neuron));
	mNumNeurons--;
}

Neuron * NeuronLayer::GetNeuronOfName(const std::string & name)
{
	Neuron* result = nullptr;
	for (auto n : mNeurons)
	{
		if (n->Name() == name)
		{
			result = n;
		}
	}
	return result;
}

std::vector<double> NeuronLayer::Update(vector<double> input)
{
	
	vector<double> outputs;
	
	for (auto n : mNeurons) {
		n->SetWeights(input);
		outputs.push_back(n->Update());
	}
	return outputs;
}

NeuronLayer::~NeuronLayer()
{
	for (auto n : mNeurons)
	{
		delete n;
	}
}
