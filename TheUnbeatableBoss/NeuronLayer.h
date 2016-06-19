#pragma once
#include"Neuron.h"
#include<functional>
/*!
\class NeuronLayer
\briefA neuron layer has a set of neurons in it and it outputs a vector of doubles, all the outputs of all it's neurons
*/
class NeuronLayer
{
	friend class NNVisualizer;
private:
	int mNumNeurons;
	std::vector<Neuron*> mNeurons;
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
	/*
	\fn Update(vector<double>)
	\brief Updates the layer
	\param The weights 
	*/
	std::vector<double> Update(vector<double> input);
	~NeuronLayer();
};

