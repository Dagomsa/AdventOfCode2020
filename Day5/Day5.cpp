// calendar.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int calculateRow(const std::string& srow);
int calculateColumn(const std::string& scolumn);
int main()
{
    uint8_t row;
    uint8_t column;

    std::ifstream input;
    input.open("Day5_1.txt");
    std::string line;
    uint32_t solution = 0;
    std::vector<std::pair<int, int>> seats;
    std::vector<int> ids;

    seats.reserve(1024);
    ids.reserve(1024);
    while (std::getline(input, line))
    {
        std::string srow = line.substr(0, 7);
        std::string scolumn = line.substr(7, 3);

        int a = calculateRow(srow);
        int b = calculateColumn(scolumn);
        seats.emplace_back(a, b);
        ids.emplace_back(a * 8 + b);
    }

    std::pair<int, int> remaining;
    for (int i = 0; i < 128; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            auto it = std::find(seats.begin(), seats.end(), std::make_pair(i, j));
            if (it == seats.end())
            {
                auto prev = std::find(ids.begin(), ids.end(), i * 8 + j - 1);
                auto next = std::find(ids.begin(), ids.end(), i * 8 + j + 1);
                if (prev != ids.end() && next != ids.end())
                {
                    remaining.first = i;
                    remaining.second = j;
                }
            }
        }
    }

    solution = remaining.first * 8 + remaining.second;
    std::cout << solution << std::endl;
}

int calculateRow(const std::string& srow)
{
    int row = 0;
    for (int i = 0; i < srow.length(); i++)
    {
        int j = srow.length() - i - 1;
        if (srow[i] == 'B')
            row += pow(2, j);
    }
    return row;
}

int calculateColumn(const std::string& scolumn)
{
    int column = 0;
    for (int i = 0; i < scolumn.length(); i++)
    {
        int j = scolumn.length() - i - 1;
        if (scolumn[i] == 'R')
            column += pow(2, j);
    }
    return column;
}