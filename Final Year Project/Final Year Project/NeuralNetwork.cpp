#include "NeuralNetwork.h"

class Neuron {};

NeuralNetwork::NeuralNetwork(const std::vector<uint> topology)
{
	//make this throw custom error

	uint numLayers = topology.size();

	for (uint layerNum = 0; layerNum < numLayers; ++layerNum)
	{
		m_layers.push_back(Layer());

		for (uint neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum)
		{
			//give last element in container
			m_layers.back().push_back(new Neuron());
			std::cout << "New Neuron created "  << std::endl;
		}
	}
}

void NeuralNetwork::FeedForward(const std::vector<double>& inputVals)
{
}

void NeuralNetwork::BackProp(const std::vector<double>& targetVals)
{
}

void NeuralNetwork::getResults(std::vector<double>& resultVals) const
{
}

NeuralNetwork::~NeuralNetwork()
{

	for (auto layer : m_layers)
	{
		for (auto neuron : layer)
		{
			std::cout << "Deleted " << neuron << std::endl;
			delete neuron;
		}
	}

}
