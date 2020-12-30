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
int main()
{
    uint16_t solution = 0;
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

    solution = container.size();
    std::cout << solution << std::endl;
}

void Part1(const std::vector<Bag>& bags, const std::string& bagtofind, std::unordered_set < std::string > & container)
{
    for (int i = 0; i < bags.size(); ++i)
    {
        for (int j = 0; j < bags[i].getChildren().size(); ++j)
        {
            if ((bags[i].getChildren())[j].compare(bagtofind) == 0)
            {
                auto success = container.insert(bags[i].getName());
                if (success.second == true)
                    Part1(bags, bags[i].getName(), container);
            }
        }
    }
}