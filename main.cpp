#include <iostream>
#include "LifeGameHeader.hpp"

int main(int argc, char** argv)
{
	std::string mode;
	std::string inputFilename;
	std::string outputFilename = "out.life";
	int countTick = 0;
	if (argc == 1)
	{
		mode = "online";
	}
	if (argc > 1)
	{
		mode = "offline";
		inputFilename = argv[1];
		for (int i = 2; i + 1 < argc; ++i)
		{
			if (argv[i] == std::string("-i"))
			{
				countTick = std::stoi(argv[i + 1]);
			}
			if (argv[i] == std::string("-o"))
			{
				outputFilename = argv[i + 1];
			}
		}
	}
	try
	{
		if (mode == "offline")
		{
			Life* lifeGame = new Life(inputFilename);
			lifeGame->Tick(countTick);
			lifeGame->Dump(outputFilename);
			std::cout << "Your game have been saved in file: " << outputFilename;
			return 0;
		}
		else if (mode == "online")
		{
			std::cout << "Do you prefer to use the default field? (Yes/No)";
			std::string answer;
			std::cin >> answer;
			Life* lifeGame;
			if (answer == "Yes") {
				lifeGame = new Life();
			} 
			else {
				std::cout << "Write the life file name: ";
				std::string inputFilename;
				std::cin >> inputFilename;
				std::cout << std::endl;
				lifeGame = new Life(inputFilename);
			}			
			lifeGame->Help();
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
	catch (const Exception& ex)
	{
		std::cout << ex.what() << " in " << ex.where();
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what();
	}
}