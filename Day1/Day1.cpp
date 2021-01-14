// Day1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

uint32_t Part1(const std::vector<uint16_t>& list);
uint32_t Part2(const std::vector<uint16_t>& list);

int main()
{
    uint16_t num;
    std::vector<uint16_t> list;
    std::ifstream input;
    input.open("input.txt");
    while (input >> num)
        list.push_back(num);

    std::sort(list.begin(), list.end());

    std::cout << "Part 1 solution: " << Part1(list) << "\n";
    std::cout << "Part 2 solution: " << Part2(list) << "\n";
}

uint32_t Part1(const std::vector<uint16_t>& list)
{
    for (int i = 0; i < list.size(); ++i)
    {
        for (int j = i; j < list.size(); ++j)
        {
            if (list[j] + list[i] == 2020)
                return list[j] * list[i];
        }
    }
}

uint32_t Part2(const std::vector<uint16_t>& list)
{
    for (int i = 0; i < list.size(); ++i)
    {
        for (int j = i; j < list.size(); ++j)
        {
            if (list[i] + list[j] > 2020)
                continue;

            for (int k = j; k < list.size(); ++k)
            {
                if (list[k] + list[i] + list[j] == 2020)
                    return list[k] * list[i] * list[j];
            }
        }
    }
}