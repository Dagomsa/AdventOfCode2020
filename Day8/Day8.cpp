// Day8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <map>

void ParseInstructions(std::map<uint16_t, std::pair<uint8_t, int>>& instructions);
int Part1(std::map<uint16_t, std::pair<uint8_t, int>>& instructions);
int Part2(std::map<uint16_t, std::pair<uint8_t, int>>& instructions);

int main()
{
    std::map<uint16_t, std::pair<uint8_t, int>> instructions;
    ParseInstructions(instructions);
    
    std::cout << "Part1 solution: " << Part1(instructions) << std::endl;
    std::cout << "Part2 solution: " << Part2(instructions) << std::endl;
}

void ParseInstructions(std::map<uint16_t, std::pair<uint8_t, int>>& instructions)
{
    uint16_t pos = 0;
    std::ifstream input;
    std::string line;
    input.open("input.txt");

    while (getline(input, line))
    {
        uint8_t i = 0; //instruction type
        if (line[0] == 'a') //acc
            i = 1;
        else if (line[0] == 'j') //jmp
            i = 2;
        else  //nop
            i = 3;

        int j = std::stoi(line.substr(4)); //instruction value
        auto p = std::make_pair(i, j);
        instructions.insert({ pos, p });
        pos++;
    }
}

int Part1(std::map<uint16_t, std::pair<uint8_t, int>>& instructions)
{
    int acc = 0;
    uint16_t pos = 0;
    std::unordered_set<int> used;

    while (true)
    {
        auto p = used.insert(pos);
        if (p.second == false)
            break;

        switch (instructions[pos].first)
        {
        case 1: //acc
            acc += instructions[pos].second;
            pos++;
            break;
        case 2: //jmp
            pos += instructions[pos].second;
            break;
        case 3: //nop
            pos++;
            break;
        }
    }
    return acc;
}

int Part2(std::map<uint16_t, std::pair<uint8_t, int>>& instructions)
{
    int acc = 0;
    uint16_t pos = 0;
    std::unordered_set<int> used;
    std::unordered_set<int> used_modpos;
    uint16_t endpos = instructions.size();
    bool testingpos = false;
    while (true)
    {
        auto p1 = used.insert(pos);
        if (!p1.second)
        {
            //Restart loop
            pos = 0;
            acc = 0;
            testingpos = false;
            used.clear();
            continue;
        }

        if (pos >= endpos) //check if 
            break;


        switch (instructions[pos].first)
        {
        case 1: //acc
        {
            acc += instructions[pos].second;
            pos++;
            break;
        }
        case 2: //jmp
        {
            if (!testingpos)
            {
                auto p2 = used_modpos.insert(pos);
                if (p2.second)
                {
                    pos++;
                    testingpos = true;
                }
                else
                    pos += instructions[pos].second;
            }
            else
                pos += instructions[pos].second;
            break;
        }
        case 3: //nop
        {
            if (!testingpos)
            {
                auto p2 = used_modpos.insert(pos);
                if (p2.second)
                {
                    pos += instructions[pos].second;
                    testingpos = true;
                }
                else
                    pos++;
            }
            else
                pos++;

            break;
        }
        }
    }
    return acc;
}

