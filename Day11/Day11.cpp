// Day11.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using m_pos_busy = std::map<std::pair<uint8_t, uint8_t>, std::pair<uint8_t, uint8_t>>;

void ReadChairsFile(m_pos_busy& chairs);
bool CalculateNextStep1(m_pos_busy& chairs);
bool CalculateNextStep2(m_pos_busy& chairs);
int CalculateAdjacentBusy1(const m_pos_busy& c, uint8_t row, uint8_t column);
int CalculateAdjacentBusy2(const m_pos_busy& c, uint8_t row, uint8_t column);
int CalculateBusyForDirection(const m_pos_busy& c, uint8_t row, uint8_t column, int up, int right);
int CountTotalBusy(const m_pos_busy& chairs);

int main()
{
    std::map<std::pair<uint8_t, uint8_t>, std::pair<uint8_t, uint8_t>> chairs;
    std::map<std::pair<uint8_t, uint8_t>, std::pair<uint8_t, uint8_t>> chairscopy;
    ReadChairsFile(chairs);
    chairscopy = chairs;

    bool unstable = true;
    while (unstable)
    {
        unstable = CalculateNextStep1(chairs);
    }
    std::cout << "Part1 solution: " << CountTotalBusy(chairs) << std::endl;

    unstable = true;
    while (unstable)
    {
        unstable = CalculateNextStep2(chairscopy);
    }
    std::cout << "Part2 solution: " << CountTotalBusy(chairscopy) << std::endl;
}

void ReadChairsFile(m_pos_busy& chairs)
{
    std::ifstream input;
    input.open("input.txt");
    std::string line;
    int nrow = 0;
    int ncolumn = 0;
    while (getline(input, line))
    {
        for (auto& c : line)
        {
            switch (c)
            {
            case 'L':
                chairs.insert(std::make_pair(std::make_pair(nrow, ncolumn), std::make_pair(1, 1))); //free
                break;
            case '#':
                chairs.insert(std::make_pair(std::make_pair(nrow, ncolumn), std::make_pair(2, 2))); //busy
                break;
            case '.':
                chairs.insert(std::make_pair(std::make_pair(nrow, ncolumn), std::make_pair(0, 0))); //floor
                break;
            }
            ncolumn++;
        }
        nrow++;
        ncolumn = 0;
    }
}

bool CalculateNextStep1(m_pos_busy& chairs)
{
    bool unstable = false;
    for (auto& c : chairs)
    {
        if (c.second.first == 0) //we dont need to calculate the adjacents of floor
            continue;

        int busy = CalculateAdjacentBusy1(chairs, c.first.first, c.first.second);
        if (busy == 0 && c.second.first == 1)
        {
            c.second.second = 2;
            unstable = true;
        }
        if (busy >= 4 && c.second.first == 2)
        {
            c.second.second = 1;
            unstable = true;
        }
    }
    for (auto& c : chairs)
    {
        c.second.first = c.second.second;
    }

    return unstable;
}

int CalculateAdjacentBusy1(const m_pos_busy& c, uint8_t row, uint8_t column)
{
    if (c.at(std::make_pair(row, column)).first == 0)
        return 0; //it doesnt matter

    int count = 0;
    for (int i = row-1; i < row + 2; i++)
    {
        for (int j = column - 1; j < column + 2; j++)
        {
            if (i == row && j == column) continue;

            std::pair<int, int> p = std::make_pair(i, j);
            if (c.find(p) != c.end())
            {
                if (c.at(p).first == 2)
                    count++;
            }
        }
    }
    return count;
}

int CountTotalBusy(const m_pos_busy& chairs)
{
    int busy = 0;
    for (auto& c : chairs)
    {
        if (c.second.first == 2)
            busy++;
    }
    return busy;
}

bool CalculateNextStep2(m_pos_busy& chairs)
{
    bool unstable = false;
    for (auto& c : chairs)
    {
        if (c.second.first == 0) //we dont need to calculate the adjacents of floor
            continue;
        int busy = CalculateAdjacentBusy2(chairs, c.first.first, c.first.second);
        if (busy == 0 && c.second.first == 1)
        {
            c.second.second = 2;
            unstable = true;
        }
        if (busy >= 5 && c.second.first == 2)
        {
            c.second.second = 1;
            unstable = true;
        }
    }
    for (auto& c : chairs)
    {
        c.second.first = c.second.second;
    }

    return unstable;
}

int CalculateAdjacentBusy2(const m_pos_busy& c, uint8_t row, uint8_t column)
{
    int count = 0;
    count += CalculateBusyForDirection(c, row, column, 1, 0);
    count += CalculateBusyForDirection(c, row, column, 1, 1);
    count += CalculateBusyForDirection(c, row, column, 0, 1);
    count += CalculateBusyForDirection(c, row, column, -1, 1);
    count += CalculateBusyForDirection(c, row, column, -1, 0);
    count += CalculateBusyForDirection(c, row, column, -1, -1);
    count += CalculateBusyForDirection(c, row, column, 0, -1);
    count += CalculateBusyForDirection(c, row, column, 1, -1);

    return count;
}

int CalculateBusyForDirection(const m_pos_busy& c, uint8_t row, uint8_t column, int up, int right)
{
    int i = up;
    int j = right;
    while (true)
    {
        std::pair<int, int> p = std::make_pair(row + i, column + j);
        if (c.find(p) != c.end())
        {
            if (c.at(p).first == 2)
            {
                return 1;
            }
            else if (c.at(p).first == 1)
                return 0;
        }
        else return 0;

        if (up < 0) i--;
        if (up > 0) i++;
        if (right < 0) j--;
        if (right > 0) j++;
    }
}