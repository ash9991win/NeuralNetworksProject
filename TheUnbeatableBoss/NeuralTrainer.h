#pragma once
//The class which trains a neural network. 
#include"NeuralNet.h"
#include<future>
class NeuralTrainer
{
private:
	const float learningConstant = 0.05f;
	NeuralNet* mNetToTrain;
	double mExpectedOutput;
	double mError;
	bool mIsCalculating;
	std::mutex mTrainerMutex;
	vector<future<void>> mThreads;
public:
	delegate<void> FinishedCalculationEvent;
	void UpdateAsync();
	void Update();
	void Update(vector<double> inputs);
#if TRAIN_WITH_DATA
	double mErrorSum;
	void TrainAsync(vector<vector<double>> in, vector<vector<double>> op);
	void Train(vector<vector<double>> in, vector<vector<double>> op);
#endif
	void AssignNetwork(NeuralNet& net) { mNetToTrain = &net; }
	void SetExpectedOutput(double output) { mExpectedOutput = output; }
	bool IsTrainerCalculating()  {
		bool result;
		{
			lock_guard<mutex> lg(mTrainerMutex);
			result = mIsCalculating;
		}
		return result;
	}
	NeuralTrainer();
	~NeuralTrainer();
};

