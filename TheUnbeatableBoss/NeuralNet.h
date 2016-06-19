#pragma once
#include"NeuronLayer.h"
enum class NeuralLayers
{
	INPUT,HIDDEN,OUTPUT
};
/*!
\class NeuralNet
\brief The NeuralNet encompasses ALL the layers of the NN
*/
class NeuralNet
{
	friend class NNVisualizer;
private:
	NeuronLayer* mInputLayer;
	NeuronLayer* mHiddenLayer;
	NeuronLayer* mOutputLayer;
public:
	/*!
	\fn Update(vector<double>)
	\brief The updation of the network with the given inputs
	\param The inputs to the network which is propogated through the layers
	\return Returns the output of the network 
	*/
	vector<double> Update(vector<double> inputs);
	/*!
	\fn AssignInputLayer(NeuronLayer&)
	\brief Assigns the inputlayer to the network
	\param The input layer to be assigned
	*/
	void AssignInputLayer(NeuronLayer& inputLayer);
	/*!
	\fn AssignHiddenLayer(NeuronLayer&)
	\brief Assigns the HiddenLayer to the network
	\param The hidden layer to be assigned
	*/
	void AssignHiddenlayer(NeuronLayer& hiddenLayer);
	/*!
	\fn AssignOutputLayer(NeuronLayer&)
	\brief Assigns the output layer to the network
	\param The output layer to be assigned
	*/
	void AssignOutputLayer(NeuronLayer& outputlayer);
	/*!
	\fn GetNeuronInLayer(string,NeuralLayers)
	\brief Gets the neuron in a given layer with the given name
	\param The name of the neuron
	\param The layer to search for the neuron
	*/
	Neuron* GetNeuronInLayer(const std::string& name, NeuralLayers layer);
	NeuralNet() = default;
	/*
	\fn ~NeuralNet()
	\brief Destroys all the layers
	*/
	~NeuralNet();
};

