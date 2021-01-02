// Day10.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

void LoadAdapters(std::vector<uint8_t>& v);
int Part1(const std::vector<uint8_t>& v);
void FindSegments(const std::vector<uint8_t>& v, std::vector<uint8_t>& pos3); //find the positions where you can only do a +3 (UNIQUE PATH)
void CalculateSegment(const std::vector<uint8_t>& v, uint64_t& result, uint16_t initsearchpos, uint16_t endsearchpos);
uint64_t Part2(const std::vector<uint8_t>& v);

void main()
{
    std::vector<uint8_t> adapters;
    LoadAdapters(adapters);
    std::cout << "Part 1 solution: " << Part1(adapters) << std::endl;
    std::cout << "Part 2 solution: " << Part2(adapters) << std::endl;
}

void LoadAdapters(std::vector<uint8_t>& v)
{
    std::ifstream input;
    input.open("input.txt");
    std::string line;

    v.push_back(0); //Treat the charging outlet near your seat as having an effective joltage rating of 0.
    uint8_t max = 0;
    while (getline(input, line))
    {
        uint8_t i = stoi(line);
        max = max > i ? max : i;
        v.push_back(i);
    }
    v.push_back(max + 3); //your device has a built-in joltage adapter rated for 3 jolts higher than the highest-rated adapter in your bag
    std::sort(v.begin(), v.end());
}

int Part1(const std::vector<uint8_t>& v)
{
    uint8_t jolt1 = 0;
    uint8_t jolt3 = 0;

    for (int i = 1; i < v.size(); i++)
    {
        if (v[i] - v[i - 1] == 1)
            jolt1++;
        if (v[i] - v[i - 1] == 3)
            jolt3++;
    }

    return jolt1 * jolt3;
}

uint64_t Part2(const std::vector<uint8_t>& v)
{
    std::vector<uint8_t> segments;

    FindSegments(v, segments);
    uint64_t segmentpaths = 1;
    uint64_t result = 1;
    uint16_t first = 0;
    uint16_t last;
    for (auto& s : segments)
    {
        last = s;
        CalculateSegment(v, segmentpaths, first, last);
        result *= segmentpaths;
        segmentpaths = 1;
        first = last;
    }
    last = v.size();
    CalculateSegment(v, segmentpaths, first, last);//last segment to end
    result *= segmentpaths;
    return result;
}

void FindSegments(const std::vector<uint8_t>& v, std::vector<uint8_t>& pos3)
{
    for (int i = 0; i < v.size() - 2; i++)
    {
        if (v[i + 1] == v[i] + 3)
            pos3.push_back(i + 1);
    }
}

void CalculateSegment(const std::vector<uint8_t>& v, uint64_t& result, uint16_t initsearchpos, uint16_t endsearchpos)
{
    for (uint16_t i = initsearchpos; i < endsearchpos; i++)
    {
        if (i + 1 < endsearchpos)
        {
            if (v[i + 1] == v[i] + 3)
            {
                initsearchpos = i + 1;
                return;
            }
            if (i + 2 < endsearchpos)
            {
                if (v[i + 2] - v[i] <= 3)
                {
                    CalculateSegment(v, result, i + 2, endsearchpos);
                    result++;
                }
                if (i + 3 < endsearchpos)
                {
                    if (v[i + 3] - v[i] <= 3)
                    {
                        CalculateSegment(v, result, i + 3, endsearchpos);
                        result++;
                    }
                }
            }
        }
    }
}


