// Day1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>

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

    std::cout << "Part 1 solution: " << Part1(list) << "\n";
    std::cout << "Part 2 solution: " << Part2(list) << "\n";
}

uint32_t Part1(const std::vector<uint16_t>& list)
{
    for (int i = 0; i < list.size(); ++i)
    {
        for (auto& l : list)
        {
            if (l + list[i] == 2020)
                return l * list[i];
        }
    }
}

uint32_t Part2(const std::vector<uint16_t>& list)
{
    for (int i = 0; i < list.size(); ++i)
    {
        for (int j = 0; j < list.size(); ++j)
        {
            if (list[i] + list[j] > 2020)
                continue;

            for (auto& l : list)
            {
                if (l + list[i] + list[j] == 2020)
                    return l * list[i] * list[j];
            }
        }
    }
}