// Day16.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <fstream>
#include <string>
#include <sstream>

using Rules = std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>;

uint32_t Part1(std::vector<int>& myticket, std::vector<std::vector<int>>& nearbytickets, Rules& rules);
uint64_t Part2(const std::vector<int>& myticket, const std::vector<std::vector<int>>& nearbytickets, const Rules& rules);
void setRule(Rules& rules, std::unordered_set<uint32_t>& valid, const std::string& line);
void setMyTicket(std::vector<int>& myticket, std::string& line);
uint32_t setNearbyTickets(std::vector<std::vector<int>>& nearbytickets, const std::unordered_set<uint32_t>& valid, std::string& line);
void DecodeStep(std::vector<std::vector<int>>& column_rules, std::vector<std::vector<int>>& rules_column, std::unordered_map<int, int>& decoded);
uint64_t CalculateFinalResult(const std::unordered_map<int, int>& decoded, const std::vector<int>& myticket);

int main()
{
    Rules rules;
    std::vector<std::vector<int>> nearbytickets;
    std::vector<int> myticket;

    std::cout << "Part 1 solution: " << Part1(myticket, nearbytickets, rules) << "\n";
    std::cout << "Part 2 solution: " << Part2(myticket, nearbytickets, rules) << "\n";
}

uint32_t Part1(std::vector<int>& myticket , std::vector<std::vector<int>>& nearbytickets, Rules& rules)
{
    uint32_t result = 0;
    std::unordered_set<uint32_t> valid;
    std::ifstream input;
    std::string line;
    bool rulesset = false;
    bool myticketset = false;
    input.open("input.txt");
    while (getline(input, line))
    {
        if (line == "" && rulesset)
        {
            myticketset = true;
            continue;
        }

        if (line == "")
        {
            rulesset = true;
            continue;
        }

        if (!rulesset)
        {
            setRule(rules, valid, line);
            continue;
        }

        if (rulesset && !myticketset)
        {
            if (line[0] == 'y') // "your ticket: " 
                continue;

            setMyTicket(myticket, line);
        }

        if (myticketset)
        {
            if (line[0] == 'n') // "nearby tickets: " 
                continue;

            result += setNearbyTickets(nearbytickets, valid, line); //returns sum of invalid numbers found in this line
        }
    }
    return result;
}

void setRule(Rules& rules, std::unordered_set<uint32_t>& valid, const std::string& line)
{
    int pos1 = line.find(":");
    int pos2 = line.find("-");
    int pos3 = line.find("or", pos2);
    int pos4 = line.find("-", pos3);

    int min = std::stoi(line.substr(pos1 + 2, pos2 - (pos1 + 2)));
    int max = std::stoi(line.substr(pos2 + 1, pos3 - 1 - (pos2 + 1)));
    auto p1 = std::make_pair(min, max);

    for (int i = min; i < max + 1; ++i)
        valid.insert(i);

    min = std::stoi(line.substr(pos3 + 3, pos4 - (pos3 + 3)));
    max = std::stoi(line.substr(pos4 + 1));
    auto p2 = std::make_pair(min, max);

    for (int i = min; i < max + 1; ++i)
        valid.insert(i);

    rules.push_back(std::make_pair(p1, p2));
}
void setMyTicket(std::vector<int>& myticket, std::string& line)
{
    for (auto& l : line)
    {
        if (l == ',')
            l = ' ';
    }
    std::stringstream ss;
    ss << line;
    std::string stmp;
    uint32_t tmp;
    while (!ss.eof())
    {
        /* extracting word by word from stream */
        ss >> stmp;

        /* Checking the given word is integer or not */
        if (std::stringstream(stmp) >> tmp)
            myticket.push_back(tmp);
    }
}
uint32_t setNearbyTickets(std::vector<std::vector<int>>& nearbytickets, const std::unordered_set<uint32_t>& valid, std::string& line)
{
    std::vector<int> thisticket;
    bool invalidticket = false;
    uint32_t result = 0;
    std::stringstream ss;
    for (auto& l : line)
    {
        if (l == ',')
            l = ' ';
    }
    ss << line;
    std::string stmp;
    uint32_t tmp;
    while (!ss.eof())
    {
        /* extracting word by word from stream */
        ss >> stmp;

        /* Checking the given word is integer or not */
        if (std::stringstream(stmp) >> tmp)
        {
            thisticket.push_back(tmp);
            bool invalidnum = (valid.find(tmp) == valid.end());
            if (invalidnum)
            {
                invalidticket = true;
                result += tmp;
            }
        }
    }
    if (!invalidticket)
        nearbytickets.push_back(thisticket);

    return result;
}


uint64_t Part2(const std::vector<int>& myticket, const std::vector<std::vector<int>>& nearbytickets, const Rules& rules)
{
    std::vector<std::vector<int>> column_rules;
    std::vector<std::vector<int>> rules_column;
    std::vector<std::vector<int>> nearby_by_column;
    std::vector<int> column;

    //Here I split all the ticket values by its positions (by column)
    column.reserve(nearbytickets.size());
    nearby_by_column.reserve(nearbytickets[0].size());
    for (int i = 0; i < nearbytickets[0].size(); ++i) //for each ticket
    {
        for (int j = 0; j < nearbytickets.size(); ++j) //for each column
            column.emplace_back(nearbytickets[j][i]);

        nearby_by_column.emplace_back(column);
        column.clear();
    }

    //For every value position (column), I check what rules fit with their values and store them in "column_rules"
    column_rules.resize(rules.size());
    for (int r = 0; r < rules.size(); ++r)
    {
        for (int i = 0; i < nearby_by_column.size(); ++i) //column
        {
            bool fitsrule = true;
            for (int j = 0; j < nearby_by_column[0].size(); ++j) //ticket
            {
                int val = nearby_by_column[i][j];
                auto rule = rules[r];
                if (!(val >= rule.first.first && val <= rule.first.second || val >= rule.second.first && val <= rule.second.second))
                {
                    fitsrule = false;
                    break;
                }
            }
            if (fitsrule)
                column_rules[i].emplace_back(r);
        }
    }

    //Here, for every rule, I store what columns are their possible candidates.
    for (int r = 0; r < rules.size(); ++r)
    {
        rules_column.push_back(std::vector<int>());
        for (int i = 0; i < column_rules.size(); ++i)
        {
            if (std::find(column_rules[i].begin(), column_rules[i].end(), r) != column_rules[i].end()) //if the rule applies to the column
                rules_column[r].push_back(i);
        }
    }

    //Solving the rules-column relationship
    std::unordered_map<int, int> decoded;
    while (decoded.size() < rules.size())
        DecodeStep(column_rules, rules_column, decoded);

    return CalculateFinalResult(decoded, myticket);
}

void DecodeStep(std::vector<std::vector<int>>& column_rules, std::vector<std::vector<int>>& rules_column, std::unordered_map<int,int>& decoded) 
{
    //decoded: key:rule , value:column
    for (int i = 0; i < column_rules.size(); ++i)
    {
        if (column_rules[i].size() == 1) //this column only has 1 possible rule
        {
            int decodedrule = column_rules[i][0];
            decoded.insert(std::make_pair(decodedrule,i));
            //for (int j = 0; j < column_rules.size(); ++j)
            for (auto &cr : column_rules)
            {
                auto it = std::find(cr.begin(), cr.end(), decodedrule);
                if (it != cr.end())
                    cr.erase(it);
            }
            rules_column[decodedrule].clear();
        }
    }

    for (int i = 0; i < rules_column.size(); ++i)
    {
        if (rules_column[i].size() == 1) //this rule only has 1 possible column
        {
            int decodedcolumn = rules_column[i][0];
            decoded.insert(std::make_pair(i, decodedcolumn));
            for (auto& rc : rules_column)
            {
                auto it = std::find(rc.begin(), rc.end(), decodedcolumn);
                if (it != rc.end())
                    rc.erase(it);
            }
            column_rules[decodedcolumn].clear();
        }
    }
}

uint64_t CalculateFinalResult(const std::unordered_map<int, int>& decoded, const std::vector<int>& myticket)
{
    uint64_t result = 1;
    //the puzzle only wants the "departure" rules, which are the first 6 rules.
    for (int i = 0; i < 6; ++i)
        result *= myticket[decoded.at(i)];

    return result;
}
