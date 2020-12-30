#pragma once
#include <vector>
#include <map>
#include <string>
class Bag
{
private:
    std::string name;
    std::vector<std::pair<int, std::string>> children;

public:
    Bag();

    static Bag parseRule(std::string& rule);
    std::string getName() const { return name; };
    std::vector<std::pair<int, std::string>> getChildren() const { return children; }

    //bool operator== (const std::string& p_name) { return name == p_name; };
};