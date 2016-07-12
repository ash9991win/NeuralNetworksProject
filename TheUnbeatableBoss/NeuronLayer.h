#pragma once
#include"Neuron.h"
#include<functional>
#include<assert.h>
/*!
\class NeuronLayer
\briefA neuron layer has a set of neurons in it and it outputs a vector of doubles, all the outputs of all it's neurons
*/
class NeuronLayer
{
	friend class NNVisualizer;
	friend class NeuralTrainer;
	friend class NeuralNet;
private:
	int mNumNeurons;
	std::vector<Neuron*> mNeurons;
	void ResetPreviousWeights() {
		for (auto neuron : mNeurons)
		{
			neuron->mPreviousWeights = neuron->mWeights;
		}
	}
public:
	/*
	\fn AddNeuron(Neuron&)
	\brief Add a given neuron to the layer
	\param The neuron to be added
	*/
	void AddNeuron(Neuron& newNeuron);
	/*
	\fn RemoveNeuron(Neuron&)
	\brief Removes a given neuron from the layer
	\param The neuron to be removed
	*/
	void RemoveNeuron(Neuron& neuron);
	/*
	\fn GetNeuronOfName(const std::string&)
	\brief Gets a neuron of  a given name
	\param The name of the neuron to be found
	\return The found neuron
	*/
	Neuron* GetNeuronOfName(const std::string& name);
	Neuron* GetNeuron(int index) { assert(index < mNeurons.size()); return mNeurons[index]; }
	/*
	\fn Update(vector<double>)
	\brief Updates the layer
	\param The weights 
	*/
	std::vector<double> Update();
	std::vector<double> Update(std::vector<double> input);
	~NeuronLayer();
};

