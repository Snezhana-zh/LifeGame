#include <iostream>
#include "LifeGameHeader.hpp"

int main()
{
	
	std::cout << "Write the life file name: ";
	std::string inputFilename;
	std::cin >> inputFilename;
	std::cout << std::endl;
	Life* lifeGame = new Life(inputFilename);
	std::cout << "Check and write the mode (offline or online): ";
	std::string mode;
	std::cin >> mode;
	std::cout << std::endl;
	if (mode == "offline")
	{
		std::cout << "Write the output file name: ";
		std::string outputFilename;
		std::cin >> outputFilename;
		std::cout << std::endl;
		std::cout << "Write the count of ticks: ";
		unsigned int countTick;
		std::cin >> countTick;
		std::cout << std::endl;
		lifeGame->Tick(countTick);
		lifeGame->Dump(outputFilename);
		std::cout << "Your game have been saved in file: " << outputFilename;
		return 0;
	}
	else if (mode == "online")
	{
		std::string action;
		while (std::getline(std::cin, action))
		{
			if (action == "exit")
			{
				return 0;
			}
			if (action == "help")
			{
				lifeGame->Help();
			}
			if (action == "dump")
			{
				std::cout << "Write the output file name: ";
				std::string outputName;
				std::cin >> outputName;
				std::cout << std::endl;
				lifeGame->Dump(outputName);
				std::cout << "Your game have been saved in file: " << outputName;
				std::cout << std::endl;
			}
			if (action == "tick")
			{
				std::cout << "Write the count of ticks: ";
				unsigned int countTick;
				std::cin >> countTick;
				std::cout << std::endl;
				lifeGame->Tick(countTick);
				lifeGame->PrintGame(std::cout);
			}
			if (action == "print")
			{
				lifeGame->PrintGame(std::cout);
			}
		}
	}
}