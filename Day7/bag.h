#pragma once
#include <vector>
#include <map>
#include <string>
class Bag
{
private:
    std::string name;
    std::vector<std::string> children;

public:
    Bag();

    static Bag parseRule(std::string& rule);
    std::string getName() const { return name; };
    std::vector<std::string> getChildren() const { return children; }
};