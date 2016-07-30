#pragma once
#include"GeneticAlgorithm.h"
#include"BossPattern.h"
class Boss;
class PatternChooser
{
private:
	Boss* mBoss;
	GeneticAlgorithm<shared_ptr<Action>> PatternSearch;
	friend int main();
public:
	void Initialize();
	void FindNextBestPattern(shared_ptr<PatternFollower>& pattern);
	PatternChooser();
	~PatternChooser();
};

