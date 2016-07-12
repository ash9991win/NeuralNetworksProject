#pragma once
#include<vector>
/*!
\class Neuron
\brief The Neuron class that acts as individual inputs to the network
*/
class Neuron
{
	friend class NNVisualizer;
	friend class NeuralTrainer;
	friend class NeuralNet;
	friend class NeuronLayer;
private:
	int mNumberOfInputs;
	std::vector<double> mInputs;
	std::vector<double> mWeights;
	std::vector<double> mPreviousWeights;
	std::function<double(double)> mActivationFunction;
	std::string mName;
	double mOutput;
	double mError;
public:
	Neuron(int numInputs,const std::string& name,std::function<double(double)> activation);
	~Neuron() = default;
	/*!
	\fn Update()
	\brief Update the neuron 
	\return The result of the neuron
	*/
	virtual double Update();
	//Set a given weight at a given index
	void SetWeight(int index, double weight);
	//Returns the weight at an index
	double GetWeight(int index);
	//Sets teh entire weights
	void SetWeights(std::vector<double> weights);
	void AssignInput(int index, double value);
	void AssignInput(std::vector<double> value);
	void ChangeInputSize(int newSize);
	//returns the name of the neuron
	const std::string& Name() const;
};

