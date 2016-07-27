#pragma once
#include"Genome.h"

    template<typename T1>
	class GeneticAlgorithm
	{
	private:
		vector<Genome<T1>> mGenomes;
		int mPopulationSize;
		double mCrossOverRate;
		double mMutationRate;
		int mChromosomeLength;
		int mGeneLength;
		int mFittestGenome;
		double mBestFitnessScore;
		double mTotalFitnessScore;
		int mGeneration;
		bool mBusy;
		Genome<T1>& RouletteSelection()
		{
			double fSlice = RandFloat() * mTotalFitnessScore;
			double cfTotal = 0.0;
			int	SelectedGenome = 0;
			for (int i = 0; i<mPopulationSize; ++i)
			{

				cfTotal += mGenomes[i].mFitness;

				if (cfTotal > fSlice)
				{
					SelectedGenome = i;
					break;
				}
			}

			return mGenomes[SelectedGenome];
		}
		void Mutate(vector<int>& bits)
		{
			for (int curBit = 0; curBit<bits.size(); curBit++)
			{
				
				if (RandFloat() < mMutationRate)
				{
					bits[curBit] = RandInt(0, Genome<T1>::MAXNUMBEROFVALUES - 1);
				}
			}
		}
		void CrossOver(const vector<int>& parent1, const vector<int>& parent2, vector<int>& child1, vector<int>& child2)
		{
			//just return parents as offspring dependent on the rate
			//or if parents are the same
			if ((RandFloat() > mCrossOverRate) || (parent1 == parent2))
			{
				child1 = parent1;
				child2 = parent2;

				return;
			}

			//determine a crossover point
			int cp = RandInt(0, mChromosomeLength - 1);

			//swap the bits
			for (int i = 0; i<cp; ++i)
			{
				child1.push_back(parent1[i]);
				child2.push_back(parent2[i]);
			}

			for (int i = cp; i<parent1.size(); ++i)
			{
				child1.push_back(parent2[i]);
				child2.push_back(parent1[i]);
			}
		}
		void UpdateFitness()
		{
			mFittestGenome = 0;
			mBestFitnessScore = 0;
			mTotalFitnessScore = 0;
			for (int i = 0; i<mPopulationSize; ++i)
			{
				auto possibleValues = Decode(mGenomes[i].mBits);
				mGenomes[i].mFitness = Genome<T1>::FitnessFunction(possibleValues);
				mTotalFitnessScore += mGenomes[i].mFitness;
				if (mGenomes[i].mFitness > mBestFitnessScore)
				{
					mBestFitnessScore = mGenomes[i].mFitness;
					mFittestGenome = i;
					if (mGenomes[i].mFitness == 1)
					{
						mBusy = false;
					}
				}
			}//next genome
		}
		vector<T1> Decode(const vector<int>& bits) const
		{
			vector<T1> results;
			for (auto bit : bits)
			{
				results.push_back(Genome<T1>::DecodingTable[bit]);
			}
			return results;
		}
		void InitializePopulation()
		{
			mGenomes.clear();

			for (int i = 0; i<mPopulationSize; i++)
			{
				mGenomes.push_back(Genome<T1>(mChromosomeLength));
			}

			//reset all variables
			mGeneration = 0;
			mFittestGenome = 0;
			mBestFitnessScore = 0;
			mTotalFitnessScore = 0;
		}
		void Epoch()
		{
			int NewBabies = 0;
			vector<Genome<T1>> vecBabyGenomes;
			while (NewBabies < mPopulationSize)
			{
				Genome<T1> mum = RouletteSelection();
				Genome<T1> dad = RouletteSelection();

				Genome<T1> baby1, baby2;
				CrossOver(mum.mBits, dad.mBits, baby1.mBits, baby2.mBits);
				Mutate(baby1.mBits);
				Mutate(baby2.mBits);
				vecBabyGenomes.push_back(baby1);
				vecBabyGenomes.push_back(baby2);
				NewBabies += 2;
			}

			mGenomes = vecBabyGenomes;
			UpdateFitness();
			++mGeneration;
		}
	public:
		delegate<void> EpochDelegate;
		GeneticAlgorithm(double cross_rat,
			double mut_rat,
			int    pop_size,
			int    num_bits,
			int    gene_len) :mCrossOverRate(cross_rat),
			mMutationRate(mut_rat),
			mPopulationSize(pop_size),
			mChromosomeLength(num_bits),
			mTotalFitnessScore(0.0),
			mGeneration(0),
			mGeneLength(gene_len),
			mBusy(false)

		{
			InitializePopulation();
		}
		//accessor methods
		int Generation() const { return mGeneration; }
		int	GetFittest() const { return mFittestGenome; }
		const Genome<T1>& GetGenome(int index) const  {
			return mGenomes[index];
		}
		const vector<Genome<T1>>& GetAllGenomes() const
		{
			return mGenomes;
		}
		 vector<T1> GetFittestSequence() const
		{
			const Genome<T1>& result = GetGenome(GetFittest());
			return Decode(result.GetBits());
		}
		bool Started() const { return mBusy; }
		void Stop() { mBusy = false; }
		void Run()
		{
			mBusy = true;
			Epoch();
			EpochDelegate.Invoke();
			mBusy = false;
		}
	};
