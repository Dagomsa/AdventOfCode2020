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
    for (int i = 0; i < bags.size(); ++i)
    {
        std::vector<std::pair<int, std::string>> children = bags[i].getChildren();
        for (int j = 0; j < children.size(); ++j)
        {
            if (children[j].second.compare(bagtofind) == 0)
            {
                auto success = container.insert(bags[i].getName());
                if (success.second == true)
                    Part1(bags, bags[i].getName(), container);
            }
        }
    }
}

void Part2(const std::vector<Bag>& bags, const std::string& bagtofind, uint32_t& sum, uint32_t mult)
{
    for (int i = 0; i < bags.size(); ++i)
    {
        if (bags[i].getName().compare(bagtofind) == 0)
        {
            std::vector<std::pair<int, std::string>> children = bags[i].getChildren();
            for (int j = 0; j < children.size(); ++j)
            {
                uint32_t mult2 = children[j].first * mult;
                sum += mult2;
                Part2(bags, children[j].second, sum, mult2);
            }
            return;
        }
    }
}