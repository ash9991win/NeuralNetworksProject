#include"pch.h"
#include "NeuralNet.h"
//returns the output of the network, The outputs of the input layer is propogated to the hidden layers and their output is passed into the output layer whose output is returned
vector<double> NeuralNet::Update(vector<double> inputs)
{
	vector<double> output;
	//process the input layer and get its output
	if (mInputLayer && mOutputLayer && mHiddenLayer)
	{
		output = mOutputLayer->Update(mHiddenLayer->Update(mInputLayer->Update(inputs)));
	}
		return (output);
}

void NeuralNet::AssignInputLayer(NeuronLayer & inputLayer)
{
	mInputLayer = &inputLayer;
}

void NeuralNet::AssignHiddenlayer(NeuronLayer & hiddenLayer)
{
	mHiddenLayer = &hiddenLayer;
}



void NeuralNet::AssignOutputLayer(NeuronLayer & outputlayer)
{
	mOutputLayer = &outputlayer;
}

Neuron * NeuralNet::GetNeuronInLayer(const std::string & name, NeuralLayers layer)
{
	Neuron* result = nullptr;
	switch (layer)
	{
	case NeuralLayers::INPUT: {
		result = mInputLayer->GetNeuronOfName(name);
		break;
	}
	case NeuralLayers::HIDDEN: {
		result = mHiddenLayer->GetNeuronOfName(name);
		break;
	}
	case NeuralLayers::OUTPUT: {
		result = mOutputLayer->GetNeuronOfName(name);
		break;

	}
	}
	return result;
}


NeuralNet::~NeuralNet()
{
	delete mInputLayer;
	delete mHiddenLayer;
	delete mOutputLayer;
}
