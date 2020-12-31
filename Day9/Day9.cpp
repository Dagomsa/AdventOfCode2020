// Day9.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <vector>

int Part1(std::deque<long long>& d);

int main()
{
    std::deque < long long> d;
    std::cout << "Part1 solution: " << Part1(d) << std::endl;
}

int Part1(std::deque<long long>& d)
{
    std::ifstream input;
    input.open("input.txt");
    std::string line;

    uint8_t pos = 0;
    while (getline(input, line))
    {
        long long newnum = stoi(line);
        if (pos < 25)
            d.push_back(newnum);
        else
        {
            bool found = false;
            for (auto& a : d)
            {
                for (auto& b : d)
                {
                    if (a == b) continue;
                    if (a + b == newnum)
                    {
                        found = true;
                        d.pop_front();
                        d.push_back(newnum);
                    }
                }
                if (found) break;
            }
            if (!found)
                return newnum;
        }
        pos++;
    }
}
