// Day17.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <tuple>

//using Data = std::map<std::tuple<int, int, int>, std::pair<bool, bool>>; //key: x,y,z pos , value: currentstate, futurestate
using Values = std::vector<std::vector<std::vector<bool>>>;

struct Data {
    Values values;
    std::set<std::tuple<int, int, int>> active;
    std::set<std::tuple<int, int, int>> consider;
};

void LoadData(Data& data);
void Step(Data& data);
void UpdateData(Data& data);

int main()
{
    Data data;
    data.values.resize(100);
    for (auto& v : data.values)
    {
        v.resize(100);
        for (auto& c : v)
            c.resize(100);
    }

    LoadData(data);

    for (int i = 0; i < 6; ++i)
        Step(data);

    std::cout << "Part 1 solution: " << data.active.size() << "\n";
}

void LoadData(Data& data)
{
    std::ifstream input;
    input.open("input.txt");
    std::string line;
    int center = data.values.size()/2;
    int ypos = center;

    while (getline(input, line))
    {
        int xpos = center;
        for (auto& l : line)
        {
            if (l == '#')
            {
                data.values[xpos][ypos][center] = true;
                data.active.insert(std::make_tuple(xpos, ypos, center));
            }
            xpos++;
        }
        ypos++;
    }
    UpdateData(data);
}

void UpdateData(Data& data)
{
    data.consider.clear();

    for (auto& a : data.active)
    {
        int ax;
        int ay;
        int az;
        std::tie(ax, ay, az) = a;

        for (int i = -1; i < 2; ++i)
        {
            for (int j = -1; j < 2; ++j)
            {
                for (int k = -1; k < 2; ++k)
                {
                    data.consider.insert(std::make_tuple(ax + i, ay + j, az + k));
                }
            }
        }
    }
}

void Step(Data& data)
{
    std::set<std::tuple<int, int, int>> changed;
    for (auto& c : data.consider)
    {
        int activeneighbours = 0;
        int cx;
        int cy;
        int cz;
        std::tie(cx, cy, cz) = c;

        for (int i = -1; i < 2; ++i)
        {
            for (int j = -1; j < 2; ++j)
            {
                for (int k = -1; k < 2; ++k)
                {
                    if (i == j && i == k && i == 0)
                        continue;

                    if (data.values[cx + i][cy + j][cz + k])
                        activeneighbours++;
                }
            }
        }

        if (data.values[cx][cy][cz]) //If a cube is active and exactly 2 or 3 of its neighbors are also active, the cube remains active. Otherwise, the cube becomes inactive.
        {
            if (activeneighbours != 2 && activeneighbours != 3)
            {
                auto t = std::make_tuple(cx, cy, cz);
                changed.insert(t);
                data.active.erase(t);
            }
        }
        else //If a cube is inactive but exactly 3 of its neighbors are active, the cube becomes active. Otherwise, the cube remains inactive.
        {
            if (activeneighbours == 3)
            {
                auto t = std::make_tuple(cx, cy, cz);
                changed.insert(t);
                data.active.insert(t);
            }
        }
    }

    for (auto& c : changed)
    {
        int x;
        int y;
        int z;
        std::tie(x, y, z) = c;
        data.values[x][y][z] = !data.values[x][y][z];
    }

    UpdateData(data);
}
