// Day13.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

void LoadBusesInfo(uint32_t& starttime, std::vector<uint64_t>& buses);
int Part1(const uint32_t& starttime, const std::vector<uint64_t>& buses);
uint64_t Part2(const std::vector<uint64_t>& buses);

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
    uint64_t t = buses[0];

    std::vector<std::pair<int, int>> pairs;
    for (int i = 0; i < buses.size(); ++i)
    {
        if (buses[i] != 0)
            pairs.push_back(std::make_pair(buses[i], i));
    }

    int multiplier = 1;
    while (true)
    {
        t += buses[0] * multiplier;
        multiplier = 1;
        bool found = true;
        for (uint16_t i = 1; i < pairs.size(); ++i)
        {
            uint64_t val = pairs[i].first;
            uint64_t pos = pairs[i].second;
            if (val - t % val != pos)
            {
                found = false;
                break;
            }
        }
        if (found)
            return t;
    }
}