
#include <iostream>
#include <vector>
#include "NeuralNetwork.h"
#include "Helper.h"



int main()
{
    std::vector<uint> topology = {5, 3, 3, 2, 1};

    NeuralNetwork nn(topology);

    std::vector<double> inputVals;
    std::vector<double> outputVals;
    std::vector<double> resultVals;

    nn.FeedForward(inputVals);
    nn.BackProp(outputVals);
    nn.getResults(resultVals);
}

