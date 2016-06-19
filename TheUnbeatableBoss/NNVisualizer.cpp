#include"pch.h"
#include "NNVisualizer.h"
#include"Neuron.h"
#include"NeuralNet.h"
#include"NeuronLayer.h"
#include"Primitive.h"
#include"ResourceManager.h"
#include<sstream>
/*
To render the neural network, you need to know how wide the netwrok is going to be. Say the width of the circle is R
then the neuron is a circle of the radius (R + length of the line). So the height of the network is the height of the max
number of neurons in a layer.
Let the number of neurons in a layer be N, then the height of the network is (R + L) * N + GapBetweenNeurons

Width of the network:

The width of one layer is : (R + L) so the width of the entire net is  : 3 * (R + L + GapBetweenLayers)

So height of the NN : (R+L)*N + GNeuron
Width of NN : 3*(R+L+GLayer)

Then draw each layer one by one:

*/
void NNVisualizer::AssignNetwork(NeuralNet & net)
{
	mNetToDisplay = &net;
	//Calculate all the dimensions
	mNeuronRadius = 50;
	mInputLineLength = 50;
	mGapBetweenNeurons = 200;
	mGapBetweenLayers = 100;

	mHeightOfInputLayer = (net.mInputLayer->mNumNeurons) * (mNeuronRadius + mInputLineLength + mGapBetweenNeurons);
	mWidthOfInputLayer = mNeuronRadius + mInputLineLength + mGapBetweenLayers;

	mHeightOfHiddenLayer = (net.mHiddenLayer->mNumNeurons) * (mNeuronRadius + mInputLineLength + mGapBetweenNeurons);
	mWidthOfHiddenLayer = mNeuronRadius + mInputLineLength + mGapBetweenLayers;

	mHeightOfOutputLayer = (net.mOutputLayer->mNumNeurons) * (mNeuronRadius + mInputLineLength + mGapBetweenNeurons);
	mWidthOfOutputLayer = mNeuronRadius + mInputLineLength + mGapBetweenLayers;

	//Total width of the net:
	mWidthOfNet = mWidthOfInputLayer + mWidthOfHiddenLayer + mWidthOfOutputLayer;
	mHeightOfNet = std::max({ mHeightOfInputLayer, mHeightOfHiddenLayer, mHeightOfOutputLayer }, [](const float& f1, const float& f2) {return f1 < f2; });

}
//The starting position of the network is : (WWindow - heightOfnet ) / 2
void NNVisualizer::AssignWindow(sf::RenderWindow & window)
{
	mWindow = &window;
	mStartingPosition.x = mInputLineLength;
	mStartingPosition.y = (mWindow->getSize().x - mHeightOfNet) / 2;
	if (mStartingPosition.y < 0)
		mStartingPosition.y = 0;
	mInputLayerPosition = mStartingPosition;
	mHiddenLayerPosition = mInputLayerPosition;
	mHiddenLayerPosition.x += mWidthOfInputLayer;
	mOutputLayerPosition = mHiddenLayerPosition;
	mOutputLayerPosition.x += mWidthOfHiddenLayer;
	auto maxWidth = std::max({ mInputLayerPosition.x,mHiddenLayerPosition.x,mOutputLayerPosition.x });
	auto maxHeight = std::max({ mInputLayerPosition.y,mHiddenLayerPosition.y,mOutputLayerPosition.y });
	if (maxWidth >= mWindow->getSize().x)
	{
		mWindow->setSize(sf::Vector2u(maxWidth, mWindow->getSize().y));
	}
	if (maxHeight >= mWindow->getSize().y)
	{
		mWindow->setSize(sf::Vector2u(mWindow->getSize().y,maxHeight));
	}
	
}

void NNVisualizer::Render()
{
	//Draw the input layer:
	//Draw the neurons 
	sf::Vector2f mInputNeuronPosition = mInputLayerPosition;
	mInputNeuronPosition.x += mInputLineLength;
	for (auto n : mNetToDisplay->mInputLayer->mNeurons)
	{
		sf::CircleShape neuronShape;
		neuronShape.setRadius(mNeuronRadius);
		neuronShape.setPosition(mInputNeuronPosition);
		neuronShape.setFillColor(sf::Color::Green);
		int numberOfInputs = n->mNumberOfInputs;
		int gapBetweenInputs = (2 * mNeuronRadius) / numberOfInputs;
		sf::Vector2f startingInputPosition = mInputNeuronPosition;
		startingInputPosition.x -= mInputLineLength;
		startingInputPosition.x -= mInputLineLength;
		startingInputPosition.y += mNeuronRadius - (numberOfInputs * gapBetweenInputs) / 2;
		for (int i = 0; i < numberOfInputs; i++)
		{
			Primitive::DrawLine(startingInputPosition.x, startingInputPosition.y, startingInputPosition.x + mInputLineLength + mGapBetweenLayers, startingInputPosition.y, sf::Color::Green);
			std::ostringstream str;
			sf::Text weightText;
			weightText.setColor(sf::Color::Black);
			sf::Vector2f position = startingInputPosition;
			position.x += mInputLineLength;
			position.y -= gapBetweenInputs;
			weightText.setScale(0.5f, 0.5f);
			weightText.setPosition(position);
			weightText.setFont(*(ResourceManager::GetGameFont()));
			if (i <n->mWeights.size())
			{
				//Display the weight

				auto weight = n->mWeights[i];
				str << weight;
				weightText.setString(str.str());

			}
			else
			{
				weightText.setString("0");
			}
			mWindow->draw(weightText);
			startingInputPosition.y += gapBetweenInputs;
		}
		//Draw output connecting to each neuron in the hidden layer
		mInputNeuronPosition.y += mGapBetweenNeurons;

		mWindow->draw(neuronShape);
		
	}
	
	sf::Vector2f mHiddenNeuronPosition = mHiddenLayerPosition;
	mHiddenNeuronPosition.x += mInputLineLength;
	for (auto n : mNetToDisplay->mHiddenLayer->mNeurons)
	{
		sf::CircleShape neuronShape;
		neuronShape.setRadius(mNeuronRadius);
		neuronShape.setFillColor(sf::Color::Black);
		neuronShape.setPosition(mHiddenNeuronPosition);
		int numberOfInputs = n->mNumberOfInputs;
		int gapBetweenInputs = (2 * mNeuronRadius) / numberOfInputs;
		//Connect to all the hidden layers
		sf::Vector2f hiddenInputPosition = mInputLayerPosition;
		hiddenInputPosition.x += mInputLineLength;
		for (int i = 0; i < mNetToDisplay->mInputLayer->mNeurons.size(); i++)
		{
			float outputlineX1 = hiddenInputPosition.x + 2 * mNeuronRadius;
			float outputlineY1 = hiddenInputPosition.y + mNeuronRadius;
			float outputlineX2 = mHiddenNeuronPosition.x + mNeuronRadius;
			float outputlineY2 = mHiddenNeuronPosition.y + mNeuronRadius;
			Primitive::DrawLine(outputlineX1,outputlineY1 ,outputlineX2 ,outputlineY2, sf::Color::Black);
			sf::Text inputLayerOutputText;
			inputLayerOutputText.setFont(*ResourceManager::GetGameFont());
			std::ostringstream str;
			sf::Vector2f textPosition;
			textPosition.x = (outputlineX1 + outputlineX2) / 2;
			textPosition.y = (outputlineY1 + outputlineY2) / 2;
			textPosition.y -= gapBetweenInputs;
			str << mNetToDisplay->mInputLayer->mNeurons[i]->mOutput;
			inputLayerOutputText.setPosition(textPosition);
			inputLayerOutputText.setColor(sf::Color::Black);
			inputLayerOutputText.setString(str.str());
			inputLayerOutputText.setScale(0.5f, 0.5f);
			mWindow->draw(inputLayerOutputText);
			hiddenInputPosition.y += mGapBetweenNeurons;
		}

		mHiddenNeuronPosition.y += mGapBetweenNeurons;
		mWindow->draw(neuronShape);
	}

	sf::Vector2f mOutputNeuronPosition = mOutputLayerPosition;
	mOutputNeuronPosition.x += mInputLineLength;
	for (auto n : mNetToDisplay->mOutputLayer->mNeurons)
	{
		sf::CircleShape neuronShape;
		neuronShape.setRadius(mNeuronRadius);
		neuronShape.setPosition(mOutputNeuronPosition);
		neuronShape.setFillColor(sf::Color::Blue);
		int numberOfInputs = n->mNumberOfInputs;
		int gapBetweenInputs = (2 * mNeuronRadius) / numberOfInputs;
		sf::Vector2f outputLayerInput = mHiddenLayerPosition;
		outputLayerInput.x += mInputLineLength;
		for (int i = 0; i < mNetToDisplay->mHiddenLayer->mNeurons.size(); i++)
		{
			float outputlineX1 = outputLayerInput.x + 2 * mNeuronRadius;
			float outputlineY1 = outputLayerInput.y + mNeuronRadius;
			float outputlineX2 = mOutputNeuronPosition.x + mNeuronRadius;
			float outputlineY2 = mOutputNeuronPosition.y + mNeuronRadius;
			Primitive::DrawLine(outputlineX1, outputlineY1, outputlineX2, outputlineY2, sf::Color::Blue);
			sf::Text inputLayerOutputText;
			inputLayerOutputText.setFont(*ResourceManager::GetGameFont());
			std::ostringstream str;
			sf::Vector2f textPosition;
			textPosition.x = (outputlineX1 + outputlineX2) / 2;
			textPosition.y = (outputlineY1 + outputlineY2) / 2;
			textPosition.y -= gapBetweenInputs;
			str << mNetToDisplay->mHiddenLayer->mNeurons[i]->mOutput;
			inputLayerOutputText.setPosition(textPosition);
			inputLayerOutputText.setColor(sf::Color::Black);
			inputLayerOutputText.setString(str.str());
			inputLayerOutputText.setScale(0.5f, 0.5f);
			mWindow->draw(inputLayerOutputText);
			outputLayerInput.y += mGapBetweenNeurons;
		}
		sf::Vector2f outputOutputLayerPosition = mOutputNeuronPosition;
		outputOutputLayerPosition.x += mNeuronRadius;
		outputOutputLayerPosition.y += mNeuronRadius;
		Primitive::DrawLine(outputOutputLayerPosition.x, outputOutputLayerPosition.y, outputOutputLayerPosition.x + 500, outputOutputLayerPosition.y, sf::Color::Blue);
		sf::Text outputOutputText;
		std::ostringstream str;
		str << n->mOutput;
		outputOutputText.setString(str.str());
		outputOutputText.setColor(sf::Color::Blue);
		outputOutputText.setFont(*ResourceManager::GetGameFont());
		auto outputOutputTextPosition = outputOutputLayerPosition;
		outputOutputTextPosition.x += 250;
		outputOutputTextPosition.y -= mInputLineLength;
		outputOutputText.setPosition(outputOutputTextPosition);

		mWindow->draw(outputOutputText);
		mOutputNeuronPosition.y += mGapBetweenNeurons;
		mWindow->draw(neuronShape);
	}
	
}

