#pragma once
#include"Genome.h"
template<typename T>
class Chromosome
{
public:
	double FitnessValue;
	vector<std::shared_ptr<Genome<T>>> mChromosome;
	Chromosome()
	{
		CreateStartingChromosome();
	}
	 static std::function<double(Chromosome&)> FitnessFunction;
	 void CreateStartingChromosome()
	 {
		 for (int i = 0; i < LengthOfChromosome; i++)
		 {
			 std::shared_ptr<Genome<T>>  genome = std::make_shared<Genome<T>>(Genome<T>::GetRandomGenome());
			 mChromosome.push_back(genome);
		 }
	 }
	 bool operator()(shared_ptr<Chromosome<T>> r)
	 {
		 return (Fitness() > r->Fitness());
	 }
	double Fitness()
	{
		FitnessValue =  FitnessFunction(*this);
		return FitnessValue;
	}
	void Update()
	{
		for_each(mChromosome.begin(), mChromosome.end(), [](std::shared_ptr<Genome<T>>& g) {g->Update(); });
	}
	void Mutate()
	{
		int i = std::rand() % mChromosome.size();
		mChromosome[i] =make_shared<Genome<T>>(Genome<T>::GetRandomGenome());
	}
	static std::shared_ptr<Chromosome> Crossover(std::shared_ptr<Chromosome> parent1, std::shared_ptr<Chromosome> parent2)
	{
		//Get first half of first parent
		shared_ptr<Chromosome> result = std::make_shared<Chromosome>();
		for (int i = 0; i < LengthOfChromosome / 2; i++)
		{
			result->mChromosome.push_back(parent1->mChromosome[i]);
		}
		for (int i = LengthOfChromosome / 2; i < LengthOfChromosome; i++)
		{
			result->mChromosome.push_back(parent2->mChromosome[i]);
		}

		return result;
	}
};