#include"pch.h"
#include "NeuralNet.h"

//returns the output of the network, The outputs of the input layer is propogated to the hidden layers and their output is passed into the output layer whose output is returned
vector<double> NeuralNet::Update()
{
	vector<double> output;
	vector<double> captureAllInputs;
	//process the input layer and get its output
	if (mInputLayer && mOutputLayer && mHiddenLayer)
	{
		output = mOutputLayer->Update(mHiddenLayer->Update(mInputLayer->Update()));
	}
		return (output);
}

vector<double> NeuralNet::Update(vector<double> inputs)
{
	vector<double> output;
	if (CheckIfPatternWasCaptured(std::forward<vector<double>>(inputs), output))
	{
		cout << "Pattern was already captured" << endl;
		return output;
	}
	/*if (mCapturedPatterns.find(inputs) != mCapturedPatterns.end())
	{
		cout << "The pattern was found" << endl;
		return mCapturedPatterns[inputs];
	}*/
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

bool NeuralNet::CheckIfInputWasCaptured(vector<double>& op)
{
	vector<double> allInputs;
	for (auto neuron : mInputLayer->mNeurons)
	{
		for (auto ip : neuron->mInputs)
		{
			allInputs.push_back(ip);
		}
	}
	return CheckIfPatternWasCaptured(std::forward<vector<double>>(allInputs), op);
	return false;
}

bool NeuralNet::CheckIfPatternWasCaptured(vector<double>&& input,vector<double>& output)
{
	static auto comparator = [](const vector<double>& lhs,const  vector<double>& rhs)
	{
		for (int i = 0; i < lhs.size(); i++)
		{
			if (lhs[i] != rhs[i])
				return false;
		}
		return true;
	};
	for (auto& pattern : mCapturedPatterns)
	{
		auto& values = pattern.first;
		double outputV;
		if (comparator(values, input))
		{
			output = pattern.second;
			return true;
		}
	}
	return false;
}


NeuralNet::~NeuralNet()
{
	delete mInputLayer;
	delete mHiddenLayer;
	delete mOutputLayer;
}
