// Day13.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_set>

void LoadBusesInfo(uint32_t& starttime, std::vector<uint64_t>& buses);
int Part1(const uint32_t& starttime, const std::vector<uint64_t>& buses);
uint64_t Part2(const std::vector<uint64_t>& buses);
uint64_t CalculateTime(std::vector<std::pair<uint64_t, uint64_t>>& buses);

int main()
{
    uint32_t starttime = 0;
    std::vector<uint64_t> buses;
    LoadBusesInfo(starttime, buses);
    int solution1 = Part1(starttime, buses);
    std::cout << "Part1 solution: " << solution1 << "\n";
    uint64_t solution2 = Part2(buses);
    std::cout << "Part2 solution: " << solution2 << "\n";
}

void LoadBusesInfo(uint32_t& starttime, std::vector<uint64_t>& buses)
{
    std::string line;
    std::ifstream input;
    input.open("input.txt");
    while (getline(input, line))
    {
        if (starttime == 0)
        {
            starttime = stoi(line);
            continue;
        }

        while (true)
        {
            auto pos = line.find(",");

            std::string ns = line.substr(0, pos);
            if (ns == "x")
                buses.push_back(0);
            else
            {
                uint16_t n = stoi(ns);
                buses.push_back(n);
            }
            line = line.substr(pos + 1, line.length());
            if (pos == line.npos)
                break;
        }
    }
}

int Part1(const uint32_t& starttime, const std::vector<uint64_t>& buses)
{
    uint32_t solution = 0;
    uint32_t min = buses[0] - starttime % buses[0];
    for (auto& b : buses)
    {
        if (b == 0) continue;
        if (b - starttime % b < min)
        {
            min = b - starttime % b;
            solution = b * min;
        }
    }
    return solution;
}

uint64_t Part2(const std::vector<uint64_t>& buses)
{
    std::vector<std::pair<uint64_t, uint64_t>> allbuses;

    for (uint16_t i = 0; i < buses.size(); ++i)
    {
        if (buses[i] != 0)
        {
            auto p = std::make_pair(buses[i], i);
            allbuses.push_back(p);
        }
    }
    return CalculateTime(allbuses);
}

uint64_t CalculateTime(std::vector<std::pair<uint64_t, uint64_t>>& buses)
{
    uint64_t t = 0;
    uint64_t step = buses[0].first;

    buses.erase(buses.begin());

    int size = buses.size();
    while (true)
    {
        for (uint16_t i = 0; i < size; ++i)
        {
            uint64_t val = buses[i].first;
            uint64_t pos = buses[i].second;
            uint64_t delay = (val - t % val);
            if ( delay == pos % val)
            {
                step *= val;
                size--;
                buses.erase(buses.begin() + i);
            }
        }
        if (size==0)
            return t;

        t += step;
    }
}