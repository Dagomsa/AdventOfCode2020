// Day12.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>

using vdirections = std::vector<std::pair<char, int>>;

class Boat
{
private:
    int posx = 0;
    int posy = 0;
    int wposx = 10;
    int wposy = 1;
    int dir = 1; // 0 = N, 1=E , 2=S, 3=W,  --  4=R, 5=L, 6=F

public:
    void moveboat(int dir, int value)
    {
        switch (dir)
        {
        case 'N':
            posy += value;
            break;
        case 'E':
            posx += value;
            break;
        case 'S':
            posy -= value;
            break;
        case 'W':
            posx -= value;
            break;
        case 'F':
            moveforward(value);
            break;
        }
    }
    void moveforward(int value)
    {
        if (dir == 0) { posy += value; return; }
        if (dir == 1) { posx += value; return; }
        if (dir == 2) { posy -= value; return; }
        if (dir == 3) { posx -= value; return; }
    }
    void rotateboat(int direction, int value)
    {
        value /= 90;
        if (direction == 'R')
            dir += value;
        else
            dir -= value;

        if (dir < 0)
            dir += 4;
        dir = dir % 4;
    }

    void movewp(char dir, int value)
    {
        switch (dir)
        {
        case 'N':
            wposy += value;
            break;
        case 'E':
            wposx += value;
            break;
        case 'S':
            wposy -= value;
            break;
        case 'W':
            wposx -= value;
            break;
        case 'F':
            moveboattowp(value);
            break;
        }
    }
    void moveboattowp(int value)
    {
        int movex = (wposx - posx) * value;
        int movey = (wposy - posy) * value;
        posx += movex;
        posy += movey;
        wposx += movex;
        wposy += movey;
    }
    void rotatewp(char direction, int value)
    {
        value /= 90;
        if (value == 2)
        {
            wposx -= 2*(wposx - posx);
            wposy -= 2*(wposy - posy);
            return;
        }
        int xdif = wposx - posx;
        int ydif = wposy - posy;
        int aux = xdif;
        if (direction == 'R' && value == 1 || direction == 'L' && value == 3)
        {
            xdif = ydif;
            ydif = -aux;
        }
        else
        {
            xdif = -ydif;
            ydif = aux;
        }
        wposx = posx + xdif;
        wposy = posy + ydif;
    }
    int getManhattanDistance()
    {
        return abs(posx) + abs(posy);
    }
};

void LoadInstructions(vdirections& instructions);
int Part1(const vdirections& instructions);
int Part2(const vdirections& instructions);

int main()
{
    vdirections instructions;
    LoadInstructions(instructions);
    int manhatan = Part1(instructions);
    std::cout << "Part1 solution: "<< manhatan << "\n";
    manhatan = Part2(instructions);
    std::cout << "Part2 solution: " << manhatan << "\n";
}

void LoadInstructions(vdirections& instructions)
{
    std::ifstream input;
    input.open("input.txt");
    char c;
    int value;
    while (input >> c >> value)
    {
        instructions.push_back(std::make_pair(c, value));
    }
}

int Part1(const vdirections& instructions)
{
    Boat boat;
    for (auto& i : instructions)
    {
        if (i.first != 'L' && i.first != 'R')
            boat.moveboat(i.first, i.second);
        else
            boat.rotateboat(i.first, i.second);
    }
    return boat.getManhattanDistance();
}

int Part2(const vdirections& instructions)
{
    Boat boat;
    for (auto& i : instructions)
    {
        if (i.first != 'L' && i.first != 'R')
            boat.movewp(i.first, i.second);
        else
            boat.rotatewp(i.first, i.second);
    }
    return boat.getManhattanDistance();
}