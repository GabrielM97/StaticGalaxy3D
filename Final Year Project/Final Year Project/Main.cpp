
#include <iostream>
#include <vector>
#include <fstream>
#include "NeuralNetwork/NeuralNetwork.h"
#include "Utilities/Helper.h"
#include "Utilities/FileReader.h"

void ShowVectorVals(std::string label, std::vector<double>& v)
{
    std::cout << label << " ";

    for (uint i = 0; i < v.size(); i++)
    {
        std::cout << v[i] << " ";
    }

    std::cout << std::endl;

}

int main()
{

    std::vector<uint> topology = {4,2,1,3};
    NeuralNetwork nn(topology);

    FileReader file = FileReader("TrainingData/data.txt", std::fstream::basic_ios::in);

    std::vector< std::vector<double>> inputVals;

    file.Read("in", inputVals, true);

    std::vector< std::vector<double>> outputVals;

    file.Read("out", outputVals);

    file.Close();

    std::vector<double> resultVals;

    std::cout << "===============Training===============" << std::endl;

    uint epoch = 5;
    uint currentEpoch = 0;

    auto startTime = std::chrono::system_clock::now();

    double score = 0.0;

    while (currentEpoch < epoch)
    {
        std::cout << currentEpoch << std::endl;

        for (uint i = 0; i < inputVals.size() * 0.7 ; i++)
        {
            nn.FeedForward(inputVals[i]);

            nn.getResults(resultVals);
            ShowVectorVals("Outputs:", resultVals);
            ShowVectorVals("Targets:", outputVals[i]);
            
            nn.BackProp(outputVals[i]);

           /* auto x = std::max_element(resultVals.begin(), resultVals.end());

            std::cout << "Awnser :" << FindIndex(resultVals, *x) + 1 << std::endl;*/

            std::cout << "Recent Average Error: " << nn.getRecentAverageError() << std::endl;

            auto x = std::max_element(resultVals.begin(), resultVals.end());

            int guess = FindIndex(resultVals, *x);

            x = std::max_element(outputVals[i].begin(), outputVals[i].end());

            int target = FindIndex(outputVals[i], *x);

            if (guess == target)
            {
                ++score;
            }

        }
        std::cout << "Accuracy: " << score / (inputVals.size() * 0.7) * 100 << " %" << std::endl;
        ++currentEpoch;
        score = 0;
    }

    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - startTime ;

    std::cout << FormatTime(elapsed_seconds) << std::endl;
   

    std::cout << "===============Testing===============" << std::endl;

    

    for (uint i = 0; i < inputVals.size()*0.3; i++)
    {
        nn.FeedForward(inputVals[i]);

        nn.getResults(resultVals);
        ShowVectorVals("Outputs:", resultVals);
        ShowVectorVals("Targets:", outputVals[i]);

        nn.BackProp(outputVals[i]);

        auto x = std::max_element(resultVals.begin(), resultVals.end());

        int guess = FindIndex(resultVals, *x);

        x = std::max_element(outputVals[i].begin(), outputVals[i].end());

        int target = FindIndex(outputVals[i], *x);

        if (guess == target)
        {
            ++score;
        }

        
    }

    double val = inputVals.size() *0.3;
    std::cout << "Accuracy: " << (score / val) * 100 << " %" << std::endl;
}

