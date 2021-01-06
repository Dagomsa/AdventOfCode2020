// Day14.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <unordered_map>

std::string DecimalToBinary(uint64_t decimal);
uint64_t BinaryToDecimal(std::string binary);

int main()
{
    std::string line;
    std::string mask;
    std::ifstream input;
    std::unordered_map<uint32_t, uint64_t> map;
    input.open("input.txt");

    while (getline(input, line))
    {
        if (line.find("mask") != line.npos)
        {
            mask = line.substr(7);
            continue;
        }

        auto pos1 = line.find("[") + 1;
        auto pos2 = line.find("]");
        uint32_t mem = stoi(line.substr(pos1, (pos2 - pos1)));
        uint64_t decimal = stoi(line.substr(pos2 + 4));
        std::string bin = DecimalToBinary(decimal);
        for (int i = 0; i < mask.length(); ++i)
        {
            if (mask[i] == 'X')
                continue;

            bin[i] = mask[i];
        }

        decimal = BinaryToDecimal(bin);
        map[mem] = decimal;
    }

    uint64_t part1 = 0;
    for (auto& m : map)
        part1 += m.second;

    std::cout << "Part1: " << part1 << "\n";
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

uint64_t BinaryToDecimal(std::string binary)
{
    binary = binary.substr(binary.find("1"));
    uint64_t result = 0;
    for (uint64_t i=0 ; i<binary.length(); ++i)
    {
        if (binary[i] == '1')
        {
            uint64_t j = binary.length() - i - 1;
            result += pow(2, j);
        }
    }
    return result;
}