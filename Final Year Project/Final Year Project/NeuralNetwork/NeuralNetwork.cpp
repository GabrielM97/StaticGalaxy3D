#include "NeuralNetwork.h"
#include "Neuron.h"
#include <cassert>

const double NeuralNetwork::BIAS = 1.0;

NeuralNetwork::NeuralNetwork(const std::vector<uint> topology):
m_error(0.0),
m_recentAverageError(0.0),
m_recentAverageSmoothgingFactor(0.0)

{
	//make this throw custom error

	try
	{
		if (topology.size() <= 1) throw Topology_Mismatch();
	}
	catch (Topology_Mismatch &e)
	{
		std::cout << "ERROR - " << e.what() << "Topology is too small. "
			<< "Must contain at least two layers - {2, 1}" << std::endl;
		exit(3);
	}

	uint numLayers = topology.size();

	for (uint layerNum = 0; layerNum < numLayers; ++layerNum)
	{
		m_layers.push_back(Layer());
		uint numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];

		for (uint neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum)
		{
			//give last element in container
			m_layers.back().push_back(new Neuron(numOutputs, neuronNum));
			std::cout << "New Neuron created "  << std::endl;
		}

		m_layers.back().back()->SetOutputVal(BIAS);
	}
}

void NeuralNetwork::FeedForward(const std::vector<double>& inputVals)
{

	try
	{
		if (inputVals.size() != m_layers[0].size() - 1)
		{
			throw Topology_Mismatch();
		}
	}
	catch (Topology_Mismatch &e)
	{
		std::cout << "ERROR - " << e.what() << "Number of inputs does not match topology. "<<
							"Number of inputs given: "<<inputVals.size() << 
							" Number of inputs in Topology: " <<
			 				m_layers[0].size() - 1 <<std::endl;
		exit(3);
	}

	//attach  input values to input neurons

	for (uint i = 0; i < inputVals.size(); i++)
	{
		m_layers[0][i]->SetOutputVal(inputVals[i]);
	}

	//forward propagation

	for (uint layerNum = 1; layerNum < m_layers.size(); ++layerNum) // looking at layer
	{
		Layer &prevLayer = m_layers[layerNum - 1];

		for (uint neuronNum = 0; neuronNum < m_layers[layerNum].size() - 1 ; ++neuronNum) // looking at neuron in layer
		{
			m_layers[layerNum][neuronNum]->FeedForward(prevLayer);
		}
	}

}

void NeuralNetwork::BackProp(const std::vector<double>& targetVals)
{

	//calculate overall net error (using RMS - Root Mean square error)
	Layer& outputLayers = m_layers.back();
	m_error = 0.0;

	for (uint n = 0; n < outputLayers.size() - 1; n++)
	{
		double delta = targetVals[n] - outputLayers[n]->GetOutputVal();

		m_error += delta * delta;
	}

	m_error /= outputLayers.size() - 1; // get average
	m_error = sqrt(m_error); // RMS

	//implement a recent average measurement 

	m_recentAverageError = (m_recentAverageError * m_recentAverageSmoothgingFactor + m_error)
							/ (m_recentAverageSmoothgingFactor + 1.0);

	// calculate output layer gradients

	for (uint n = 0; n < outputLayers.size() - 1 ; ++n)
	{
		outputLayers[n]->CalcOutputGradients(targetVals[n]);
	}

	// calculate hidden layer gradients

	for (uint layerNum = m_layers.size() -2 ; layerNum  > 0; --layerNum)
	{
		Layer& hiddenLayer = m_layers[layerNum];
		Layer& nextLayer = m_layers[layerNum + 1];

		for (uint n = 0; n < hiddenLayer.size(); ++n)
		{
			hiddenLayer[n]->CalcHiddenGradients(nextLayer);
		}
	}
	//for all layers up to the first hidden layer, update weights

	for (uint layerNum = m_layers.size() - 1 ; layerNum > 0; --layerNum)
	{
		Layer& layer = m_layers[layerNum];
		Layer& prevLayer = m_layers[layerNum - 1];

		for (uint n = 0; n < layer.size() - 1; ++n)
		{
			layer[n]->UpdateInputWeights(prevLayer);
		}
	}

}

void NeuralNetwork::getResults(std::vector<double>& resultVals) const
{
	resultVals.clear();

	for (uint n = 0; n < m_layers.back().size() - 1; ++n)
	{
		resultVals.push_back(m_layers.back()[n]->GetOutputVal());
	}
}

NeuralNetwork::~NeuralNetwork()
{

	for (auto layer : m_layers)
	{
		for (auto neuron : layer)
		{
			delete neuron;
		}
	}

}
