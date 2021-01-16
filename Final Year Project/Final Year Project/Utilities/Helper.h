#pragma once
#include <vector>
#include <iostream>
#include <exception>
#include <ctime>
#include <chrono>
#include <sstream>
#include <algorithm>

class Neuron;

typedef unsigned int uint;
typedef std::vector<Neuron*> Layer;

static std::string FormatTime(std::chrono::duration<double>elapsed_seconds)
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

static int FindIndex(std::vector<double> v, double k)
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



struct Topology_Mismatch : public std::exception
{
	const char* what() const throw ()
	{
		return "Topology Mismatch Execption: ";
	}
};

