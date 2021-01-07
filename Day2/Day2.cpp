// Day2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::ifstream input;
    input.open("input.txt");
    std::string line;
    uint32_t result1 = 0;
    uint32_t result2 = 0;
    while (getline(input, line))
    {
        uint8_t min;
        uint8_t max;
        char c;
        std::string password;

        auto pos1 = line.find("-");
        min = std::stoi(line.substr(0, pos1));

        auto pos2 = line.find(" ");
        max = std::stoi(line.substr(pos1+1, pos2-pos1+1));

        c = line[pos2 + 1];

        password = line.substr(pos2 + 4);

        uint8_t n = std::count(password.begin(), password.end(), c);

        if (min <= n && n <= max)
            result1++;

        bool first = password[min - 1] == c;
        bool second = password[max - 1] == c;
        if (first && !second || !first && second)
            result2++;
    }

    std::cout << "Part1 solution: " << result1 << "\n";
    std::cout << "Part2 solution: " << result2 << "\n";
}