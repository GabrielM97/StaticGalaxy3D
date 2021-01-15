
#include <iostream>
#include <vector>
#include "NeuralNetwork/NeuralNetwork.h"
#include "Utilities/Helper.h"
#include <ctime>
#include <chrono>
#include <sstream>
#include <algorithm>

std::string FormatTime(std::chrono::duration<double>elapsed_seconds)
{
    uint time = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_seconds).count();

    std::cout << "Time : " << time << std::endl;

    uint hour = time / 360000;
    time = time % 360000;
    uint min = time / 60000;
    time = time % 60000;
    uint sec = time / 1000;
    time = time % 1000;
    uint millis = time;

    std::stringstream ss;

    ss << "Elapsed Time: " << hour << "h:"
        << min << "m:" << sec << "s:" << millis << "ms\n";

    return ss.str();
}

int FindIndex(std::vector<double> v, double k)
{
    auto it = find(v.begin(), v.end(), k);

    // If element was found
    if (it != v.end())
    {

        // calculating the index
        // of K
        int index = it - v.begin();
        
        return index;
    }
    else {
        
        return -1;
    }
}

int main()
{
    
    std::vector<uint> topology = {4, 4, 8};
    NeuralNetwork nn(topology);

    std::vector< std::vector<double>> inputVals = { {0, 0, 0, 1},
                                                    {0, 0, 1, 0},
                                                    {0, 0, 1, 1}, 
                                                    {0, 1, 0, 0}, 
                                                    {0, 1, 0, 1},
                                                    {0, 1, 1, 0}, 
                                                    {0, 1, 1, 1}, 
                                                    {1, 0, 0, 0}};

    std::vector< std::vector<double>> outputVals = { {1,0,0,0,0,0,0,0},
                                                     {0,1,0,0,0,0,0,0},
                                                     {0,0,1,0,0,0,0,0},
                                                     {0,0,0,1,0,0,0,0},
                                                     {0,0,0,0,1,0,0,0},
                                                     {0,0,0,0,0,1,0,0},
                                                     {0,0,0,0,0,0,1,0},
                                                     {0,0,0,0,0,0,0,1}};
    std::vector<double> resultVals;

    std::cout << "===============Training===============" << std::endl;

    uint epoch = 100;
    uint currentEpoch = 0;

    auto startTime = std::chrono::system_clock::now();

    while (currentEpoch < epoch)
    {
        std::cout << currentEpoch << std::endl;

        for (uint i = 0; i < inputVals.size(); i++)
        {
            nn.FeedForward(inputVals[i]);
            nn.getResults(resultVals);
            nn.BackProp(outputVals[i]);

            for (auto res : resultVals)
            {
                std::cout << res << std::endl;
            }
        }

        ++currentEpoch;
    }

    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - startTime ;

    std::cout << FormatTime(elapsed_seconds) << std::endl;
   
    inputVals = {{1, 0, 0, 0},//8
                 {0, 0, 1, 0},//2
                 {0, 1, 1, 0},//6
                 {0, 0, 1, 0},//2
                 {1, 0, 0, 0},//8
                 {0, 1, 0, 1},//5
                 {0, 0, 1, 0},//2
                 {0, 0, 0, 1} };//1


    std::cout << "===============Testing===============" << std::endl;
    for (uint i = 0; i < inputVals.size(); i++)
    {
        
        nn.FeedForward(inputVals[i]);
        nn.getResults(resultVals);
        //nn.BackProp(outputVals[i]);

       
        auto x = std::max_element(resultVals.begin(), resultVals.end());

      /*  for (auto res : resultVals)
        {
            std::cout << res << std::endl;
        }*/

        std::cout<< "Awnser :"  << FindIndex(resultVals, *x) + 1 << std::endl ;
    }

    while (true)
    {
        std::string binery;

        std::cout << "Enter a binery number between 1-8 \n";

        std::cin >> binery;

        std::vector<double> vals;

        for (auto bit : binery)
        {
            vals.push_back(bit - '0');
        }


        nn.FeedForward(vals);
        nn.getResults(resultVals);

        auto x = std::max_element(resultVals.begin(), resultVals.end());

        std::cout << "Awnser :" << FindIndex(resultVals, *x) + 1 << std::endl;
    }
}

