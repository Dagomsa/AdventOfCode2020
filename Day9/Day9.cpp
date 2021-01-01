// Day9.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <vector>

int Part1();
int Part2(uint64_t invalid);

int main()
{
    uint64_t invalidnum = Part1();
    std::cout << "Part1 solution: " << invalidnum << std::endl;
    std::cout << "Part2 solution: " << Part2(invalidnum) << std::endl;
}

int Part1()
{
    std::deque <uint64_t> d;
    std::ifstream input;
    input.open("input.txt");
    std::string line;

    uint8_t pos = 0;
    while (getline(input, line))
    {
        uint64_t newnum = stoll(line);
        if (pos < 25)
        {
            d.push_back(newnum);
            pos++;
        }        
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
                        break;
                    }
                }
                if (found) break;
            }
            if (!found)
                return newnum;
        }
    }
}

int Part2(uint64_t invalid)
{
    std::deque <uint64_t> d;
    std::ifstream input;
    input.open("input.txt");
    std::string line;

    uint64_t sum = 0;
    uint64_t min = 0;
    uint64_t max = 0;

    while (getline(input, line))
    {
        uint64_t newnum = stoll(line);
        max = newnum > max ? newnum : max;
        if (sum < invalid)
        {
            sum += newnum;
            d.push_back(newnum);
        }

        while (sum > invalid)
        {
            sum -= d.front();
            d.pop_front();
        }

        if (sum == invalid)
        {
            min = max;
            for (auto& a : d)
                min = min < a ? min : a;
            return min + max;
        }
    }
}
