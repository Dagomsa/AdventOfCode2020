// Day4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>

class Passport {
private:
    uint16_t byr = 0;
    uint16_t iyr = 0;
    uint16_t eyr = 0;
    std::string hgt = "";
    std::string hcl = "";
    std::string ecl = "";
    std::string pid = "";
    uint16_t cid = 0;
    
public:
    void reset()
    {
        byr = 0;
        iyr = 0;
        eyr = 0;
        hgt = "";
        hcl = "";
        ecl = "";
        pid = "";
        cid = 0;
    }
    void setbyr(uint16_t b) { byr = b; }
    void setiyr(uint16_t b) { iyr = b; }
    void seteyr(uint16_t b) { eyr = b; }
    void sethgt(const std::string& b) { hgt = b; }
    void sethcl(const std::string& b) { hcl = b; }
    void setecl(const std::string& b) { ecl = b; }
    void setpid(const std::string& b) { pid = b; }
    bool validateNumberOfKeys()
    {
        return byr != 0 && iyr != 0 && eyr != 0 && hgt != "" && hcl != "" && ecl != "" && pid != "";
    }
    bool validateValues()
    {
        if (byr < 1920 || byr > 2002)
            return false;
        if (iyr < 2010 || iyr > 2020)
            return false;
        if (eyr < 2020 || eyr > 2030)
            return false;

        std::string unit = hgt.substr(hgt.length() - 2);
        auto val = stoi(hgt.substr(0, hgt.length() - 2));
        if (unit != "cm" && unit != "in")
            return false;

        if (unit == "in") {
            if (val < 59 || val > 76)
                return false;
        }
        else
        {
            if (val < 150 || val > 193)
                return false;
        }

        if (hcl[0] != '#')
            return false;

        if (hcl.length() != 7)
            return false;

        std::string hcltest = "abcdef1234567890";
        for (int i=1 ; i<hcl.length(); ++i)
        {
            if (hcltest.find(hcl[i]) == hcl.npos)
                return false;
        }
        
        if (ecl.length() != 3)
            return false;
        
        std::string ecltest = "amb blu brn gry grn hzl oth";
        if (ecltest.find(ecl) == ecltest.npos)
            return false;

        if (pid.size() != 9)
            return false;

        std::string pidtest = "0123456789";
        for (auto& c : pid)
        {
            if (pidtest.find(c) == pidtest.npos)
                return false;
        }
        return true;
    }
};

int main()
{
    std::ifstream input;
    input.open("input.txt");
    std::string line;

    uint8_t nkeys;
    Passport p;
    uint16_t result1 = 0;
    uint16_t result2 = 0;
    while (getline(input, line))
    {
        if (line == "")
        {
            bool b1 = p.validateNumberOfKeys();
            result1 += b1 ? 1 : 0;
            if (b1)
                result2 += p.validateValues() ? 1 : 0;

            p.reset();
            continue;
        }

        int pos = 0;

        pos = line.find("byr");
        if (pos != line.npos)
        {
            auto pos2 = line.find(" ", pos);
            p.setbyr(std::stoi(line.substr(pos + 4, pos2 - (pos + 4))));
        }

        pos = line.find("iyr");
        if (pos != line.npos)
        {
            auto pos2 = line.find(" ",pos);
            p.setiyr(std::stoi(line.substr(pos + 4, pos2 - (pos + 4))));
        }

        pos = line.find("eyr");
        if (pos != line.npos)
        {
            auto pos2 = line.find(" ", pos);
            p.seteyr(std::stoi(line.substr(pos + 4, pos2 - (pos + 4))));
        }

        pos = line.find("hgt");
        if (pos != line.npos)
        {
            auto pos2 = line.find(" ", pos);
            p.sethgt(line.substr(pos + 4, pos2 - (pos + 4)));
        }

        pos = line.find("hcl");
        if (pos != line.npos)
        {
            auto pos2 = line.find(" ", pos);
            p.sethcl(line.substr(pos + 4, pos2 - (pos + 4)));
        }

        pos = line.find("ecl");
        if (pos != line.npos)
        {
            auto pos2 = line.find(" ", pos);
            p.setecl(line.substr(pos + 4, pos2 - (pos + 4)));
        }

        pos = line.find("pid");
        if (pos != line.npos)
        {
            auto pos2 = line.find(" ", pos);
            p.setpid(line.substr(pos + 4, pos2 - (pos + 4)));
        }

    }
    //Last passport
    result1 += p.validateNumberOfKeys() ? 1 : 0;
    result2 += p.validateValues() ? 1 : 0;

    std::cout << "Part1 solution: " << result1 << "\n";
    std::cout << "Part2 solution: " << result2 << "\n";
}