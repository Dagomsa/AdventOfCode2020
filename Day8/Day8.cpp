// Day8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <map>

int main()
{
    std::ifstream input;
    std::string line;
    input.open("input.txt");
    std::map<uint16_t, std::pair<uint8_t, int>> instructions;

    uint16_t pos = 0;
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
    
    int acc = 0;
    pos = 0;
    std::unordered_set<int> used;

    while (true)
    {
        auto p = used.insert(pos);
        if (p.second == false)
            break;

        switch (instructions[pos].first)
        {
        case 1:
            acc += instructions[pos].second;
            pos++;
            break;
        case 2:
            pos += instructions[pos].second;
            break;
        case 3:
            pos++;
            break;
        }
    }

    std::cout << acc << std::endl;
}
