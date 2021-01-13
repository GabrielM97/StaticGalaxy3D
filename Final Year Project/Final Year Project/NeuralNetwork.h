#pragma once
#include <iostream>
#include <vector>
#include "Helper.h"

class NeuralNetwork
{
public:

	NeuralNetwork(const std::vector<uint> topology);
	void FeedForward(const std::vector<double>& inputVals);
	void BackProp(const std::vector<double>& targetVals);
	void getResults(std::vector<double>& resultVals) const;

	~NeuralNetwork();

private:

	std::vector<Layer> m_layers; // m_layers[layerNum][neuronNum]
};

