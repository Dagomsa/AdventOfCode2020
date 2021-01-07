#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main()
{
    std::ifstream input;
    input.open("input.txt");
    std::string line;
    uint32_t solution1 = 0;
    uint32_t solution2 = 0;
    std::vector<std::pair<int, int>> seats;
    std::vector<int> ids;

    while (std::getline(input, line))
    {
        for (auto& l : line)
        {
            if (l == 'B' || l == 'R')
                l = '1';
            else
                l = '0';
        }

        uint32_t a = stoi(line.substr(0, 7), 0, 2);
        uint32_t b = stoi(line.substr(7, 3), 0, 2);
        seats.push_back(std::make_pair(a, b));
        ids.push_back(a * 8 + b);
    }

    for (const auto& i : ids)
        solution1 = solution1 > i ? solution1 : i;

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

    solution2 = remaining.first * 8 + remaining.second;
    std::cout << "Part 1 solution: " << solution1 << std::endl;
    std::cout << "Part 2 solution: " << solution2 << std::endl;
}