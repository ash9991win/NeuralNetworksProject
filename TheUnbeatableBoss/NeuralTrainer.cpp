#include"pch.h"
#include "NeuralTrainer.h"
#include<mutex>
using namespace std;
void NeuralTrainer::UpdateAsync()
{
	mThreads.emplace_back(std::async([this]() {Update(); }));
}
//Given an expected output, adjust the weights till the error becomes marginal
void NeuralTrainer::Update()
{
	if (mNetToTrain)
	{
		{
			lock_guard<mutex> lg(mTrainerMutex);
				mIsCalculating = true;
		}
		std::cout << "The expected output is " << mExpectedOutput << endl;
		//Calculate output layer's error
		auto outputLayer = mNetToTrain->mOutputLayer;
		auto hiddenLayer = mNetToTrain->mHiddenLayer;
		auto inputLayer = mNetToTrain->mInputLayer;
		outputLayer->ResetPreviousWeights();
		hiddenLayer->ResetPreviousWeights();
		inputLayer->ResetPreviousWeights();
		while (abs(outputLayer->mNeurons[0]->mOutput - mExpectedOutput) >= ERROR_RATE)
		{
			for (int k = 0; k < outputLayer->mNeurons.size(); k++)
			{
				auto outputNeuron = outputLayer->mNeurons[k];
				outputNeuron->mError = (mExpectedOutput - outputNeuron->mOutput) * (outputNeuron->mOutput) * (1 - outputNeuron->mOutput);
				for (int j = 0; j < hiddenLayer->mNeurons.size(); j++)
				{
					outputNeuron->mWeights[j] += LEARNING_RATE * outputNeuron->mError * hiddenLayer->mNeurons[j]->mOutput + ( 0.9 * outputNeuron->mPreviousWeights[j]);
					outputNeuron->mPreviousWeights[j] = LEARNING_RATE * outputNeuron->mError * hiddenLayer->mNeurons[j]->mOutput;
				}
			}
			for (int j = 0; j < hiddenLayer->mNeurons.size(); j++)
			{
				//calculate the sum for this particular input
				double errorConstant = 0;
				double output = hiddenLayer->mNeurons[j]->mOutput;
				for (int k = 0; k < outputLayer->mNeurons.size(); k++)
				{
					errorConstant += outputLayer->mNeurons[k]->mError * outputLayer->mNeurons[k]->mWeights[j];
				}
				hiddenLayer->mNeurons[j]->mError = output * (1 - output) * errorConstant;
				for (int i = 0; i < inputLayer->mNeurons.size(); i++)
				{
					hiddenLayer->mNeurons[j]->mWeights[i] += LEARNING_RATE * hiddenLayer->mNeurons[j]->mError * inputLayer->mNeurons[i]->mOutput + ( MOMENTUM * hiddenLayer->mNeurons[j]->mPreviousWeights[i]);
					hiddenLayer->mNeurons[j]->mPreviousWeights[i] = LEARNING_RATE * hiddenLayer->mNeurons[j]->mError * inputLayer->mNeurons[i]->mOutput;
				}
			}
			mNetToTrain->Update();
		}
		auto output = mNetToTrain->Update();
		cout << "The obtained output is" << output[0] << endl;
		{
			lock_guard<mutex> lg(mTrainerMutex);
			mIsCalculating = false;
		}
		FinishedCalculationEvent.Invoke();
	}
}

void NeuralTrainer::Update(vector<double> inputs)
{
	if (mNetToTrain)
	{
		mNetToTrain->AssignInput(inputs);
		Update();
	}
}
#if TRAIN_WITH_DATA
void NeuralTrainer::TrainAsync(vector<vector<double>> in, vector<vector<double>> op)
{
	mThreads.emplace_back(std::async([this,in,op]() {Train(in, op); }));
}
void NeuralTrainer::Train(vector<vector<double>> SetIn, vector<vector<double>> SetOut)
{
	//This function will train a given network to weigh itself, till 
	//it provides the correct weights for the given inputs
	
	mErrorSum = 100;
	auto inputLayer = mNetToTrain->mInputLayer;
	auto outputLayer = mNetToTrain->mOutputLayer;
	auto hiddenLayer = mNetToTrain->mHiddenLayer;
	int cycle = 0;
	while (mErrorSum > ERROR_RATE)
	{
		vector<double>::iterator  curWeight;
		vector<Neuron*>::iterator curNrnOut, curNrnHid;

		//this will hold the cumulative error value for the training set

		//run each input pattern through the network, calculate the errors and update
		//the weights accordingly
		for (int vec = 0; vec < SetIn.size(); ++vec)
		{
			//first run this input vector through the network and retrieve the outputs
			vector<double> outputs = mNetToTrain->Update(SetIn[vec]);

			//return if error has occurred

			//for each output neuron calculate the error and adjust weights
			//accordingly
			for (int op = 0; op < outputLayer->mNeurons.size(); ++op)
			{
				//first calculate the error value
				double err = (SetOut[vec][op] - outputs[op]) * outputs[op]
					* (1 - outputs[op]);

				//keep a record of the error value
				outputLayer->mNeurons[op]->mError = err;

				//update the SSE. (when this value becomes lower than a
				//preset threshold we know the training is successful)
				mErrorSum += (SetOut[vec][op] - outputs[op]) *
					(SetOut[vec][op] - outputs[op]);

				curWeight = outputLayer->mNeurons[op]->mWeights.begin();
				curNrnHid = hiddenLayer->mNeurons.begin();

				//for each weight up to but not including the bias
				while (curWeight != outputLayer->mNeurons[op]->mWeights.end() - 1)
				{
					//calculate the new weight based on the backprop rules
					*curWeight += err * LEARNING_RATE * (*curNrnHid)->mOutput;

					++curWeight; ++curNrnHid;
				}

				//and the bias for this neuron
				*curWeight += err * LEARNING_RATE * -1;
			}

			//**moving backwards to the hidden layer**
			curNrnHid = hiddenLayer->mNeurons.begin();

			int n = 0;

			//for each neuron in the hidden layer calculate the error signal
			//and then adjust the weights accordingly
			while (curNrnHid != hiddenLayer->mNeurons.end())
			{
				double err = 0;

				curNrnOut = outputLayer->mNeurons.begin();

				//to calculate the error for this neuron we need to iterate through
				//all the neurons in the output layer it is connected to and sum
				//the error * weights
				while (curNrnOut != outputLayer->mNeurons.end())
				{
					err += ((*curNrnOut)->mError) *((*curNrnOut)->mWeights[n]);

					++curNrnOut;
				}

				//now we can calculate the error
				err *= ((*curNrnHid)->mOutput) * (1 - ((*curNrnHid)->mOutput));

				//for each weight in this neuron calculate the new weight based
				//on the error signal and the learning rate
				int numInputs = inputLayer->mNeurons[0]->mNumberOfInputs;
				for (int w = 0; w < numInputs; ++w)
				{
					//calculate the new weight based on the backprop rules
					(*curNrnHid)->mWeights[w] += err * LEARNING_RATE * SetIn[vec][w];
				}

				//and the bias
				(*curNrnHid)->mWeights[numInputs] += err * LEARNING_RATE * -1;

				++curNrnHid;
				++n;
			}

		}//next input vector
		cycle++;
		system("cls");
		cout << cycle << endl;
	}
}
#endif


NeuralTrainer::NeuralTrainer()
	:mIsCalculating(false)
{
}


NeuralTrainer::~NeuralTrainer()
{
	for (auto& f : mThreads)
	{
		f.get();
	}
}
