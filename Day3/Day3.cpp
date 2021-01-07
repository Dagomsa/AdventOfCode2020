// Day3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>

uint32_t CountTrees(const std::vector<std::pair<uint32_t, uint32_t>>& map, uint8_t xvel, uint8_t yvel, uint16_t columnlength, uint16_t rowlength);

int main()
{
    std::ifstream input;
    input.open("input.txt");
    std::string line;

    std::vector<std::pair<uint32_t, uint32_t>> treepos;
    uint32_t row = 0;
    while (getline(input, line))
    {
        for (uint16_t i = 0; i < line.length(); ++i)
        {
            if (line[i] == '#')
                treepos.push_back(std::make_pair(i, row));
        }
        row++;
    }
    uint16_t columnlength = line.length();
    uint16_t rowlength = row;

    std::cout << "Part 1 solution: " << CountTrees(treepos,3,1, columnlength, rowlength) << "\n";

    uint64_t result2 = 1;
    result2 *= CountTrees(treepos, 1, 1, columnlength, rowlength);
    result2 *= CountTrees(treepos, 3, 1, columnlength, rowlength);
    result2 *= CountTrees(treepos, 5, 1, columnlength, rowlength);
    result2 *= CountTrees(treepos, 7, 1, columnlength, rowlength);
    result2 *= CountTrees(treepos, 1, 2, columnlength, rowlength);

    std::cout << "Part 2 solution: " << result2 << "\n";
}

uint32_t CountTrees(const std::vector<std::pair<uint32_t, uint32_t>>& treepos, uint8_t xvel, uint8_t yvel, uint16_t columnlength, uint16_t rowlength)
{
    uint32_t xpos = 0;
    uint32_t ypos = 0;
    uint32_t result = 0;
    while (ypos < rowlength)
    {
        xpos += xvel;
        xpos = xpos % columnlength;
        ypos += yvel;
        auto b = std::find(treepos.begin(), treepos.end(), std::make_pair(xpos, ypos));
        if (b != treepos.end())
            result++;
    }

    return result;

}