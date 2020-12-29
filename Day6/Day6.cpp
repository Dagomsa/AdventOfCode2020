// Day6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

int main()
{
	uint32_t solution = 0;
	
	std::ifstream input;
	std::string line;
	input.open("input.txt");
	std::string group;

	// ------------------ PART 1 START -------------
	/*while (getline(input, line))
	{
		for (auto& c : line)
		{
			if (group.find(c) == group.npos)
				group += c;
		}
		if (line == "")
		{
			solution += group.length();
			group.clear();
		}
	}
	solution += group.length(); //last group */
	// ------------------ PART 1 END ------------



	// ------------------ PART 2 START ------------
	bool skipgroup = false;
	while (getline(input, line))
	{
		if (line == "")
		{
			solution += group.length();
			group.clear();
			skipgroup = false;
		}
		if (!skipgroup)
		{
			if (group == "")
				group = line;
			else
			{
				std::vector<int> erasepos;
				for (uint8_t i = 0; i < group.length(); ++i)
				{
					auto it = line.find(group[i]);
					if (it == group.npos)
						erasepos.push_back(i);
				}

				for (int8_t i = erasepos.size() - 1; i >= 0; --i)
					group.erase(erasepos[i] , 1);

				if (group.empty())
					skipgroup = true;
			}
		}
	}
	solution += group.length(); //last group
	// ------------------ PART 2 END ------------




	std::cout << solution << std::endl;
}
