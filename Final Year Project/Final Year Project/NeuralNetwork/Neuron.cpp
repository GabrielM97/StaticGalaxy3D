#include "Neuron.h"

const double Neuron::LEARNING_RATE = 0.2;
const double Neuron::MOMENTUM_RATE = 0.5;

Neuron::Neuron(uint numOutputs, uint index):
m_index(index),
m_outputVal(0.0),
m_gradient(0.0)
{
	for (uint outputNum = 0; outputNum < numOutputs; ++outputNum)
	{
		m_outputWeights.push_back(Connection());
		m_outputWeights.back().weight = RandomWeight();
	}
}

void Neuron::FeedForward(const Layer& prevLayer)
{
	double sum = 0.0;

	// sum of previous layer's outputs and bias multiplied by their weights 

	for (uint n = 0; n < prevLayer.size(); n++)
	{
		sum += prevLayer[n]->GetOutputVal() *
		prevLayer[n]->m_outputWeights[m_index].weight;
	}

	m_outputVal = ActivationFunction(sum);

}

void Neuron::CalcOutputGradients(const double targetVals)
{
	double delta = targetVals - m_outputVal;
	m_gradient = delta * ActivationFunctionDerivative(m_outputVal);
}

void Neuron::CalcHiddenGradients(const Layer& nextLayer)
{
	double dow = sumDOW(nextLayer);
	m_gradient = dow * ActivationFunctionDerivative(m_outputVal);
}

void Neuron::UpdateInputWeights(Layer& prevLayer)
{
	for (uint n = 0; n < prevLayer.size(); ++n)
	{
		Neuron& neuron = *prevLayer[n];
		double oldDeltaWeight = neuron.m_outputWeights[m_index].deltaWeight;

		double newDeltaWeight =
			LEARNING_RATE
			* neuron.GetOutputVal()
			* m_gradient
			+ MOMENTUM_RATE
			* oldDeltaWeight;

		neuron.m_outputWeights[m_index].deltaWeight = newDeltaWeight;
		neuron.m_outputWeights[m_index].weight += newDeltaWeight;

	}
}

double Neuron::RandomWeight()
{
	return rand() / double(RAND_MAX);
}

double Neuron::ActivationFunction(double x)
{
	//tanh - output range [-1.0..1.0]
	return tanh(x);
}

double Neuron::ActivationFunctionDerivative(double x)
{
	//tanh derivitive
	return 1.0 - x * x;
}

double Neuron::sumDOW(const Layer& nextLayer) const
{
	double sum = 0.0;

	//sum of all contributions 

	for (uint n = 0; n < nextLayer.size()-1; ++n)
	{
		sum += m_outputWeights[n].weight * nextLayer[n]->m_gradient;
	}

	return sum;
}
