#pragma once
#include "../Utilities/Helper.h"
#include <cstdlib>
#include <cmath>


struct Connection
{
	double weight;
	double deltaWeight;
};

class Neuron
{

public:

	Neuron(uint numOutputs, uint index);

	void SetOutputVal(uint val) { m_outputVal = val; };
	double GetOutputVal() const { return m_outputVal; }; 
	
	void FeedForward(const Layer &prevLayer);
	void CalcOutputGradients(double targetVals);
	void CalcHiddenGradients(const Layer &nextLayer);
	void UpdateInputWeights(Layer &prevLayer);


private:
	uint m_index;
	double m_outputVal;
	double m_gradient;
	static const double LEARNING_RATE;
	static const double MOMENTUM_RATE;
	std::vector<Connection> m_outputWeights;
	static double RandomWeight(); 
	static double ActivationFunction(double x);
	static double ActivationFunctionDerivative(double x);
	double sumDOW(const Layer& nextLayer) const ;
};

