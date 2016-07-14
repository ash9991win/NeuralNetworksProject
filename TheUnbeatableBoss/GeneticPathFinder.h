#pragma once
#include"GeneticAlgorithm.h"
class GeneticPathFinder
{
private:
	pair<int, int> SourceIndex;
	pair<int, int> DestinationIndex;
public:
	GeneticAlgorithm<Dir> GBrain;
	GeneticPathFinder(sf::Vector2f startingPosition, sf::Vector2f endingPosition);
	void FindPath();
	~GeneticPathFinder();
};

