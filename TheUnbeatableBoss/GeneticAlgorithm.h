#pragma once
#include"Chromosome.h"
template<typename T>

class GeneticAlgorithm
{
private:
	vector<shared_ptr<Chromosome<T>>> GenerationPool;
public:
	void CreateGenerations()
	{
		for (int i = 0; i < POPULATIONSIZE; i++)
		{
			auto ch = make_shared<Chromosome<T>>();
			ch->Fitness();
			GenerationPool.push_back(ch);
		}
	}
	shared_ptr<Chromosome<T>> GenerateASolution()
	{
		
		double MaxFitness = 10;
		while (MaxFitness > 0)
		{
			/*
			For each chromosome in the generation,
			choose two with the highest fitness
			Crossover and mutate
			then check the fitness of the produced solution, if within the error rate break
			if not, remove the least fit chromosome from the generation pool
			add the obtained one into the pool

			*/
			//Step 1
			//Choose the two highest 
			std::sort(GenerationPool.begin(), GenerationPool.end());
			//Get the first two
			auto parent1 = GenerationPool[0];
			auto parent2 = GenerationPool[1];
			MaxFitness = parent1->Fitness();
			typename shared_ptr<Chromosome<T>> child = Chromosome<T>::Crossover(parent1, parent2);
			child->Mutate();
			GenerationPool.push_back(child);
		}
		std::sort(GenerationPool.begin(), GenerationPool.end());
		auto maxChromosome = GenerationPool[0];
		return maxChromosome;
	}
};

