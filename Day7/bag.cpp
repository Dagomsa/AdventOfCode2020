#include "bag.h"

Bag::Bag()
{
	name = "";
}
Bag Bag::parseRule(std::string& rule)
{
	Bag bag;

	//get name
	auto it = rule.find(" bags");
	bag.name = rule.substr(0, it).c_str();
	rule.erase(0, it + 14);

	if (it = rule.find("no other bags") != rule.npos)
		return bag;


	//get children
	it = rule.find(" bag");
	while (it != rule.npos)
	{
		//get child
			//number
		uint8_t num = std::stoi(rule.c_str()); //gets the first int

		auto it2 = rule.find(" ") + 1; //after number
		auto it3 = rule.find(" ", it2);
		it3 = rule.find(" ", it3 + 1); //assuming each colour is always defined by 2 words
		std::pair<int, std::string> p = std::make_pair(num, rule.substr(it2, it3 - it2));
		bag.children.push_back(p);
		if (num == 1) //bag in singular
			rule.erase(0, it3 + 6);
		else //bags in plural
			rule.erase(0, it3 + 7);

		it = rule.find(" bag");
	}
	return bag;
}