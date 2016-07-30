#include"pch.h"
#include "PatternChooser.h"
#include"World.h"
#include"Boss.h"
#include"Player.h"
#include"ActionFactory.h"
DECLARE_GENOME(shared_ptr<Action>)
void PatternChooser::Initialize()
{
	mBoss = World::FindActorsOfType(Boss::TypeIdClass())[0]->As<Boss>();
	
	for (auto& action : ActionFactory::ActionList)
	{
		Genome<shared_ptr<Action>>::AddPossibleValue(action, action->Name());
	}
	Genome<shared_ptr<Action>>::FitnessFunction = [](vector<shared_ptr<Action>> actions) {
		//the fitness of a pattern would be the average of all its effectiveness
		static auto Boss = World::FindActorsOfType(Boss::TypeIdClass())[0];
		static auto Player = World::FindActorsOfType(Player::TypeIdClass())[0];
		double fitness = 0;
		/*for (auto& action : actions)
		{
			fitness += action->Effectiveness();
		}*/
		fitness += Player->mHealth;
		fitness -= Boss->mHealth;
		//fitness /= actions.size();
		if (fitness == 0)
			fitness = 1;
		return 1 - (1 / fitness);
	};
    
}

void PatternChooser::FindNextBestPattern(shared_ptr<PatternFollower>& pattern)
{
	PatternSearch.Run();
	pattern->AssignActions(PatternSearch.GetFittestSequence());
}

PatternChooser::PatternChooser()
	:PatternSearch(CROSSOVER_RATE,MUTATION_RATE,POP_SIZE,CHROMO_LENGTH,GENE_LENGTH)
{
}


PatternChooser::~PatternChooser()
{
}
