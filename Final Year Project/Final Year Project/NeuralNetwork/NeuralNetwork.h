#pragma once
#include <iostream>
#include <vector>
#include "../Utilities/Helper.h"

class NeuralNetwork
{
public:

	NeuralNetwork(const std::vector<uint> topology);
	void FeedForward(const std::vector<double>& inputVals);
	void BackProp(const std::vector<double>& targetVals);
	void getResults(std::vector<double>& resultVals) const;
	double getRecentAverageError() { return m_recentAverageError; };

	~NeuralNetwork();

private:

	std::vector<Layer> m_layers; // m_layers[layerNum][neuronNum]
	double m_error;
	double m_recentAverageError;
	double m_recentAverageSmoothgingFactor;

	static const double BIAS;
};

