// Day14.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <unordered_map>
#include <unordered_set>

std::string DecimalToBinary(uint64_t decimal);

int main()
{
    std::string line;
    std::string smask;
    uint64_t applymask;
    uint64_t ignoremask;
    std::ifstream input;
    std::unordered_map<uint64_t, uint64_t> map1;
    std::unordered_map<uint64_t, uint64_t> map2;
    input.open("input.txt");
    std::unordered_set<uint64_t> xpos;
    while (getline(input, line))
    {
        if (line.find("mask") != line.npos)
        {
            xpos.clear();
            smask = line.substr(7);
            std::string s_applymask = smask;
            std::string s_ignoremask = smask;

            for (int i = 0; i < smask.length(); ++i)
            {
                if (smask[i] == 'X')
                {
                    xpos.insert(i);
                    s_ignoremask[i] = '1';
                    s_applymask[i] = '0';
                }
                else
                {
                    s_ignoremask[i] = '0';
                    if (smask[i] == '1')
                        s_applymask[i] = '1';
                    else
                        s_applymask[i] = '0';
                }
            }
            applymask = std::stoull(s_applymask, 0, 2); //convert binary to unsigned int
            ignoremask = std::stoull(s_ignoremask, 0, 2); //convert binary to unsigned int
            continue;
        }

        auto pos1 = line.find("[") + 1;
        auto pos2 = line.find("]");
        uint64_t mem = stoull(line.substr(pos1, (pos2 - pos1)));
        uint64_t val = stoull(line.substr(pos2 + 4));
        uint64_t val2 = val;

        val = (val & ignoremask) | applymask;
        map1[mem] = val;

        //logic part2
        std::vector<uint64_t> memorylocations;
        mem = (mem & ~ignoremask) | applymask;

        uint64_t initialmem = mem;
        for (int i = 0; i < pow(2, xpos.size()); ++i)
        {
            mem = initialmem;
            std::string lsmask = "000000000000000000000000000000000000";
            std::string it = DecimalToBinary(i);
            int a = it.length() - 1;
            for (auto& x : xpos)
            {
                lsmask[x] = it[a];
                a--;
            }

            uint64_t limask = stoull(lsmask, 0, 2);
            mem = mem | limask;
            memorylocations.push_back(mem);
        }
        for (int i = 0; i < memorylocations.size(); ++i)
        {
            map2[memorylocations[i]] = val2;
        }
    }

    uint64_t part1 = 0;
    for (auto& m : map1)
        part1 += m.second;

    uint64_t part2 = 0;
    for (auto& m : map2)
        part2 += m.second;

    std::cout << "Part1: " << part1 << "\n";
    std::cout << "Part2: " << part2 << "\n";
}

std::string DecimalToBinary(uint64_t decimal)
{
    int result[36] = {0}; //The bitmask is always given as a string of 36 bits
    std::string resultr;
    for (int i = 0; decimal > 0; i++)
    {
        result[i] = decimal % 2;
        decimal /= 2;
    }

    for (int i = 35; i >= 0; --i)
        resultr.append(std::to_string(result[i]));
        
    return resultr;
}