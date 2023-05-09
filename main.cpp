#include<iostream>
#include<string>
#include "Tokenizer.h"
#include "Parser.h"
#include <sstream>


int main() 
{
	try 
	{
		bool flag = true; 
		while (flag)
		{
			std::string input;
			std::stringstream buffer;
			std::vector<std::string> v;
			std::cout << "\Enter expression\n";

			std::getline(std::cin, input);
			buffer << input;

			while (buffer >> input)
			{
				v.push_back(input);
			}

			Tokenizer Lexer(v);	// tokenize strings  
			Parser p(Lexer.getStack());
			std::cout << p.getResult();


			std::cout << "\nPress (Q) to terminate other wise any key to continue\n";
			std::getline(std::cin, input); 

			if (input == "Q" || input == "q")
			{
				flag = false; 
			}


		}

		

	}
	catch (std::exception &e) 
	{
		std::cerr << e.what(); 
	}

	return 0; 

}