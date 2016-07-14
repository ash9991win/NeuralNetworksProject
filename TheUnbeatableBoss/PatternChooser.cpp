#include"pch.h"
#include "PatternChooser.h"
#include"World.h"
#include"Boss.h"
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
		return 1 / (RandFloat() + 1);
	};
    
}

void PatternChooser::FindNextBestPattern(shared_ptr<BossPattern>& pattern)
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
