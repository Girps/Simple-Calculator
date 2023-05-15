#include<iostream>
#include<string>
#include "Tokenizer.h"
#include "Parser.h"
#include <sstream>


int main() 
{	
	bool flag = true;
	do
	{
		try
		{


			printf("\nEnter an expression Q to terminate\n >> ");
			std::string line;

			std::getline(std::cin, line);

			if (line == "Q" || line == "q")
			{
				flag = false;
			}
			else
			{
				Tokenizer t(line);
				auto v = t.getVector();

				Parser syn(t.getStack());
				std::cout << "= "  << syn.getResult();
			}


		}
		catch (std::exception& e)
		{
			std::cerr << e.what();
		}
	}
	while (flag); 

	printf("Program terminated");

	return 0; 

}