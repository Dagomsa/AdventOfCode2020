// Day15.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_map>

uint64_t Solve(uint64_t desiredturn);
int main()
{
    std::cout << "Part1 solution :" << Solve(2020) << "\n";
    std::cout << "Part1 solution :" << Solve(30000000) << "\n";
}

uint64_t Solve(uint64_t desiredturn)
{
    uint64_t solution1 = 0;

    std::unordered_map<int, int> historic;

    //Puzzle input
    historic[18] = 1;
    historic[11] = 2;
    historic[9] = 3;
    historic[0] = 4;
    historic[5] = 5;
    historic[1] = 6;

    uint64_t turn = 7;
    uint64_t consider = 1;
    bool existed = false;
    int prevconsidervalue = -1;
    while (turn < desiredturn + 1)
    {
        if (!existed)
        {
            historic[consider] = turn - 1;
            consider = 0;
            turn++;
            existed = true; //0 always existed, for this input
            //existed = historic.find(0) != historic.end(); // if didn't exist, should be like this
            continue;
        }

        int a;
        if (prevconsidervalue > 0)
            a = turn - 1 - prevconsidervalue;
        else
            a = turn - 1 - historic[consider];

        existed = historic.find(a) != historic.end();
        if (existed)
            prevconsidervalue = historic[a];
        else
            prevconsidervalue = -1;

        historic[consider] = turn - 1;
        historic[a] = turn;

        consider = a;
        turn++;
    }
    return consider;
}