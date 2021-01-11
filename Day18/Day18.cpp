// Day18.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

uint64_t Part(int i);
uint64_t Solve1(std::string& str);
uint64_t Solve2(std::string& str);
void operate(std::string& str);
void SolveSums(std::string& deepop);
void operatesum(std::string& str);
int CalculateDepthMapParentheses(const std::string& str, std::string& strmap);
int CalculateDepthMapSum(const std::string& str, std::string& strmap);

int main()
{
    std::cout << "Part 1 solution: " << Part(1) << "\n";
    std::cout << "Part 2 solution: " << Part(2) << "\n";
}
uint64_t Part(int i)
{
    uint64_t result = 0;
    std::ifstream input;
    input.open("input.txt");
    std::string line;
    auto function = i == 1 ? Solve1 : Solve2;
    while (getline(input, line))
    {
        result += function(line);
    }
    return result;
}

uint64_t Solve1(std::string& str)
{
    std::string strmap;
    int maxdeep = CalculateDepthMapParentheses(str, strmap);

    while (maxdeep >= 0)
    {
        std::string level = std::to_string(maxdeep);
        int pos1 = strmap.find(level);
        int pos2 = strmap.find_first_not_of(level, pos1);

        if (maxdeep != 0)
        {
            std::string deepop = str.substr(pos1, pos2 - pos1);
            operate(deepop);
            str.replace(pos1, pos2 - pos1, deepop);
            maxdeep = CalculateDepthMapParentheses(str, strmap);
        }
        else
        {
            operate(str);
            return stoull(str);
        }
    }
}

uint64_t Solve2(std::string& str)
{
    std::string strmap;
    int maxdeep = CalculateDepthMapParentheses(str, strmap);

    while (maxdeep >= 0)
    {
        std::string level = std::to_string(maxdeep);
        int pos1 = strmap.find(level);
        int pos2 = strmap.find_first_not_of(level, pos1);

        if (maxdeep != 0)
        {
            std::string deepop = str.substr(pos1, pos2 - pos1);
            deepop.erase(deepop.begin());
            deepop.erase(deepop.end() - 1);

            SolveSums(deepop);
            operate(deepop);
            str.replace(pos1, pos2 - pos1, deepop);
            maxdeep = CalculateDepthMapParentheses(str, strmap);
        }
        else
        {
            SolveSums(str);
            operate(str);
            return stoull(str);
        }
    }
}

void operate(std::string& str)
{
    ////Erase parentesis
    if (str.find("(") != str.npos)
    {
        str.erase(str.begin());
        str.erase(str.end()-1);
    }

    std::string stmp;
    uint64_t num1;
    uint64_t num2;
    char op;
    std::stringstream ss;
    ss << str;
    bool first = true;
    while (!ss.eof())
    {
        ss >> stmp;
        if (first)
        {
            num1 = stoi(stmp);
            first = false;
            continue;
        }
        if (std::stringstream(stmp) >> num2)
        {
            if (op == '+')
                num1 += num2;
            if (op == '*')
                num1 *= num2;
        }
        else
            std::stringstream(stmp) >> op;
    }
    str = std::to_string(num1);
}

void SolveSums(std::string& deepop)
{
    std::string strmap2;
    int maxdeepsum = CalculateDepthMapSum(deepop, strmap2);
    while (maxdeepsum > 0)
    {
        std::string level = std::to_string(maxdeepsum);
        int pos1s = strmap2.find(level);
        int pos2s = strmap2.find_first_not_of(level, pos1s);
        if (pos2s == strmap2.npos)
            pos2s = strmap2.length();
        std::string deepopsum = deepop.substr(pos1s, pos2s - pos1s);
        operatesum(deepopsum);
        deepop.replace(pos1s, pos2s - pos1s, deepopsum);
        maxdeepsum = CalculateDepthMapSum(deepop, strmap2);
    }
}

void operatesum(std::string& str)
{
    ////Erase parentesis
    if (str.find("(") != str.npos)
    {
        str.erase(str.begin());
        str.erase(str.end() - 1);
    }

    std::string stmp;
    uint64_t num1;
    uint64_t result = 0;
    std::stringstream ss;
    ss << str;
    while (!ss.eof())
    {
        ss >> stmp;
        if (std::stringstream(stmp) >> num1)
            result += num1;
    }
    str = std::to_string(result);
}

int CalculateDepthMapParentheses(const std::string& str, std::string& strmap)
{
    strmap.clear();
    uint8_t deep = 0;
    uint8_t maxdeep = 0;
    for (auto& c : str)
    {
        if (c == '(')
        {
            deep++;
            maxdeep = maxdeep > deep ? maxdeep : deep;
        }
        strmap.append(std::to_string(deep));

        if (c == ')')
            deep--;
    }
    return maxdeep;
}

int CalculateDepthMapSum(const std::string& str, std::string& strmap)
{
    strmap.clear();
    uint8_t deep = 0;
    uint8_t maxdeep = 0;
    for (auto& c : str)
        strmap.append("0");

    int ini = 0;
    int end = 0;
    while (true)
    {
        int pos = str.find("+" , end);
        if (pos == str.npos)
            return maxdeep;

        maxdeep = 1;
        ini = str.rfind(" ", pos - 2) + 1;
        end = str.find("*", pos);
        if (end == str.npos)
            end = str.length() - 1;
        else
            end -= 2;

        for (int i = ini; i <= end; ++i)
            strmap[i] = '1';
    }
}