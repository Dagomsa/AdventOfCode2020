// Day17.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <tuple>

using Values3D = std::vector<std::vector<std::vector<bool>>>;
using Values4D = std::vector<std::vector<std::vector<std::vector<bool>>>>;

struct Data3D {
    Values3D values;
    std::set<std::tuple<int, int, int>> active;
    std::set<std::tuple<int, int, int>> consider;
};

struct Data4D {
    Values4D values;
    std::set<std::tuple<int, int, int, int>> active;
    std::set<std::tuple<int, int, int, int>> consider;
};

void LoadData3D(Data3D& data);
void LoadData4D(Data4D& data);
void Step3D(Data3D& data);
void Step4D(Data4D& data);
void UpdateData3D(Data3D& data);
void UpdateData4D(Data4D& data);

uint32_t Part1();
uint32_t Part2();

int main()
{
    std::cout << "Part 1 solution: " << Part1() << "\n";
    std::cout << "Part 2 solution: " << Part2() << "\n";
}

void LoadData3D(Data3D& data)
{
    std::ifstream input;
    input.open("input.txt");
    std::string line;
    int center = data.values.size() / 2;
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
    UpdateData3D(data);
}

void LoadData4D(Data4D& data)
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
                data.values[xpos][ypos][center][center] = true;
                data.active.insert(std::make_tuple(xpos, ypos, center, center));
            }
            xpos++;
        }
        ypos++;
    }
    UpdateData4D(data);
}

void UpdateData3D(Data3D& data)
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
                    data.consider.insert(std::make_tuple(ax + i, ay + j, az + k));
            }
        }
    }
}

void UpdateData4D(Data4D& data)
{
    data.consider.clear();

    for (auto& a : data.active)
    {
        int ax;
        int ay;
        int az;
        int aw;
        std::tie(ax, ay, az, aw) = a;

        for (int i = -1; i < 2; ++i)
        {
            for (int j = -1; j < 2; ++j)
            {
                for (int k = -1; k < 2; ++k)
                {
                    for (int f = -1; f < 2; ++f)
                        data.consider.insert(std::make_tuple(ax + i, ay + j, az + k, aw + f));
                }
            }
        }
    }
}

void Step3D(Data3D& data)
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
        int w;
        std::tie(x, y, z) = c;
        data.values[x][y][z] = !data.values[x][y][z];
    }

    UpdateData3D(data);
}

void Step4D(Data4D& data)
{
    std::set<std::tuple<int, int, int, int>> changed;
    for (auto& c : data.consider)
    {
        int activeneighbours = 0;
        int cx;
        int cy;
        int cz;
        int cw;
        std::tie(cx, cy, cz, cw) = c;

        for (int i = -1; i < 2; ++i)
        {
            for (int j = -1; j < 2; ++j)
            {
                for (int k = -1; k < 2; ++k)
                {
                    for (int f = -1; f < 2; ++f)
                    {
                        if (i == j && i == k && i == f && i == 0)
                            continue;

                        if (data.values[cx + i][cy + j][cz + k][cw + f])
                            activeneighbours++;
                    }
                }
            }
        }

        if (data.values[cx][cy][cz][cw]) //If a cube is active and exactly 2 or 3 of its neighbors are also active, the cube remains active. Otherwise, the cube becomes inactive.
        {
            if (activeneighbours != 2 && activeneighbours != 3)
            {
                auto t = std::make_tuple(cx, cy, cz, cw);
                changed.insert(t);
                data.active.erase(t);
            }
        }
        else //If a cube is inactive but exactly 3 of its neighbors are active, the cube becomes active. Otherwise, the cube remains inactive.
        {
            if (activeneighbours == 3)
            {
                auto t = std::make_tuple(cx, cy, cz, cw);
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
        int w;
        std::tie(x, y, z, w) = c;
        data.values[x][y][z][w] = !data.values[x][y][z][w];
    }

    UpdateData4D(data);
}


uint32_t Part1()
{
    Data3D data;
    data.values.resize(100);
    for (auto& v : data.values)
    {
        v.resize(100);
        for (auto& c : v)
        {
            c.resize(100);
        }
    }

    LoadData3D(data);

    for (int i = 0; i < 6; ++i)
        Step3D(data);

    return data.active.size();
}

uint32_t Part2()
{
    Data4D data;
    data.values.resize(100);
    for (auto& v : data.values)
    {
        v.resize(100);
        for (auto& c : v)
        {
            c.resize(100);
            for (auto& d : c)
                d.resize(100);
        }
    }

    LoadData4D(data);

    for (int i = 0; i < 6; ++i)
        Step4D(data);

    return data.active.size();
}