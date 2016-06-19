#pragma once
class NeuralNet;
/*!
\class NNVisualizer
\brief The class the displays the neural network
*/
class NNVisualizer
{
	NeuralNet* mNetToDisplay;
	sf::RenderWindow* mWindow;
	float mNeuronRadius; 
	float mInputLineLength;
	float mGapBetweenNeurons;
	float mGapBetweenLayers;
	float mWidthOfNet;
	float mHeightOfNet;
	float mHeightOfInputLayer;
	float mWidthOfInputLayer;
	float mWidthOfHiddenLayer;
	float mHeightOfHiddenLayer;
	float mWidthOfOutputLayer;
	float mHeightOfOutputLayer;
	sf::Vector2f mInputLayerPosition;
	sf::Vector2f mHiddenLayerPosition;
	sf::Vector2f mOutputLayerPosition;
	sf::Vector2f mStartingPosition;
public:
	/*!
	\fn AssignNetwork(NeuralNet)
	\brief Assign the given network to be drawn
	\param The network to be drawn
	*/
	void AssignNetwork(NeuralNet& net);
	/*!
	\fn AssignWindow(sf::RenderWindow& )
	\brief Assign the window to render to
	\param The window to render to
	*/
	void AssignWindow(sf::RenderWindow& window);
	/*!
	\fn Render
	\brief renders the given network
	*/
	void Render();
	NNVisualizer() = default;
	~NNVisualizer() = default;
};

