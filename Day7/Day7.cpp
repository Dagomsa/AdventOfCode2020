// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "bag.h"
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include <unordered_set>

void Part1(const std::vector<Bag>& bags, const std::string& bagtofind, std::unordered_set<std::string>& container);
void Part2(const std::vector<Bag>& bags, const std::string& bagtofind, uint32_t& sum, uint32_t mult);
int main()
{
    uint16_t solution1 = 0;
    uint32_t solution2 = 0;
    std::ifstream input;
    input.open("input.txt");
    std::string line;
    std::vector<Bag> bags;
    std::unordered_set<std::string> container;
    while (getline(input, line))
    {
        bags.push_back(Bag::parseRule(line));
    }
    Part1(bags, "shiny gold" , container);
    solution1 = container.size();

    Part2(bags, "shiny gold", solution2 , 1);

    std::cout << "Part1: " << solution1 << std::endl;
    std::cout << "Part2: " << solution2 << std::endl;
}

void Part1(const std::vector<Bag>& bags, const std::string& bagtofind, std::unordered_set < std::string > & container)
{
    for (auto &b : bags)
    {
        std::vector<std::pair<int, std::string>> children = b.getChildren();
        for (auto &c : children)
        {
            if (c.second.compare(bagtofind) == 0)
            {
                std::string bname = b.getName();
                auto success = container.insert(bname);
                if (success.second)
                    Part1(bags, bname, container);
            }
        }
    }
}

void Part2(const std::vector<Bag>& bags, const std::string& bagtofind, uint32_t& sum, uint32_t mult)
{
    for (auto &b : bags)
    {
        if (b.getName().compare(bagtofind) == 0)
        {
            std::vector<std::pair<int, std::string>> children = b.getChildren();
            for (auto &c : children)
            {
                uint32_t mult2 = c.first * mult;
                sum += mult2;
                Part2(bags, c.second, sum, mult2);
            }
            return;
        }
    }
}