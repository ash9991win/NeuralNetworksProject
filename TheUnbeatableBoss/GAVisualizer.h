#pragma once
//Class for visualizing a GEnetic algorithm. Typically it displays the following:

//The current generation number,the current set of chromosomes ( their encoded versions) 
// A decoding legend 
#include"Genome.h"
#include"GeneticAlgorithm.h"
#include<sstream>
#include<mutex>
template<typename T>
class GAVisualizer
{
	sf::RenderWindow* mWindow;
	float windowWidth;
	float windowHeight;
	GeneticAlgorithm<T>* mGA;
	vector<Genome<T>> Genomes;
	std::mutex mGALock;
	map<int, string> stringTable;
	sf::Text *LegendTable;
	int rowLegendCount;
	sf::Text generationText;
	sf::Text ChromosomeLabel;
	sf::Text Fitnesslabel;
	int MaxFitnessIndex;
public:
	void AssignGA(GeneticAlgorithm<T>& ga)
	{
		mGA = &ga;
		mGA->EpochDelegate.Bind( &GAVisualizer<T>::UpdateGeneration,this);
		stringTable = Genome<T>::StringDecoder;
	
		
	}
	void PopulateLegends()
	{
		rowLegendCount = stringTable.size();
		LegendTable = new sf::Text[rowLegendCount];
		sf::Vector2f startingPositionOfTable;
		startingPositionOfTable.x = windowWidth / 2 + 25;
		startingPositionOfTable.y = windowHeight / 2;
		for (int i = 0; i < rowLegendCount; i++)
		{
			ostringstream stream;
			stream << i << "     " << stringTable[i];
			LegendTable[i].setString(stream.str());
			LegendTable[i].setColor(sf::Color::Green);
			LegendTable[i].setFont(*(ResourceManager::GetGameFont()));
			LegendTable[i].setPosition(startingPositionOfTable);
			startingPositionOfTable.y += 50;
		}
	}
	 void UpdateGeneration()
	{
		{
			std::lock_guard<mutex> g(mGALock);
				Genomes = mGA->GetAllGenomes();
				MaxFitnessIndex = mGA->GetFittest();
		}
	}

     void AssignWindow(sf::RenderWindow & window)
	{
		mWindow = &window;
		windowWidth = mWindow->getSize().x;
		windowHeight = mWindow->getSize().y;

		

		ChromosomeLabel.setString("CHROMOSOME");
		ChromosomeLabel.setPosition(0, 10);
		ChromosomeLabel.setColor(sf::Color::Black);
		ChromosomeLabel.setFont(*(ResourceManager::GetGameFont()));
		Fitnesslabel.setString("FITNESS");
		Fitnesslabel.setPosition(320, 10);
		Fitnesslabel.setColor(sf::Color::Black);
		Fitnesslabel.setFont(*(ResourceManager::GetGameFont()));
		
	}

	void Render()
	{
		//First display the generation number
		ostringstream generationString;
		generationString << "Generation Number:    " << mGA->Generation();
		generationText.setString(generationString.str());
		generationText.setPosition(windowWidth / 2 + 50, 0);
		generationText.setColor(sf::Color::Black);
		generationText.setFont(*(ResourceManager::GetGameFont()));
		mWindow->draw(generationText);
		//Display the first child as a table
		for (int i = 0; i < rowLegendCount; i++)
		{
			mWindow->draw(LegendTable[i]);
		}
		mWindow->draw(ChromosomeLabel);
		mWindow->draw(Fitnesslabel);
		{
			std::lock_guard<mutex> lock(mGALock);
				for (int i = 0; i < Genomes.size(); i++)
				{
					//Display the chromosome first
					ostringstream chromosomeStream;
					for (int j = 0; j < Genomes[i].mBits.size(); j++)
					{
						chromosomeStream << Genomes[i].mBits[j];
					}
					chromosomeStream << "                     " << Genomes[i].mFitness;
					sf::Text chromosomeText;
					chromosomeText.setString(chromosomeStream.str());
					chromosomeText.setFont(*(ResourceManager::GetGameFont()));
					chromosomeText.setPosition(0,50 + (i * 30 ));
					if (i == MaxFitnessIndex)
					{
						chromosomeText.setColor(sf::Color::Red);
					}
					else
					{
						chromosomeText.setColor(sf::Color::Black);
					}
					//chromosomeText.setScale(0.45f, 0.45f);

					mWindow->draw(chromosomeText);


				}
		}
	}
};

